/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "BoltzmannSolverScalar.h"
#include "Function.h"
#include <fstream>
#include <limits>
#include "MooseVariableScalar.h"

registerMooseObject("CraneApp", BoltzmannSolverScalar);

template <>
InputParameters
validParams<BoltzmannSolverScalar>()
{
  InputParameters params = validParams<GeneralUserObject>();
  params.addCoupledVar("mole_fractions",
                       "The AuxVariables representing the mole fractions of the species being "
                       "considered in Bolsig+.");
  params.addCoupledVar("reduced_field",
                       "The Variable/AuxVariable representing the reduced field. (Optional.)");
  params.addCoupledVar("neutral_density",
                       "The neutral density of the plasma (background + excited states).");
  params.addCoupledVar("ionization_fraction",
                       "The AuxVariable representing the ionization fraction of the plasma. "
                       "(Currently: n_e / n_tot)");
  params.addRequiredParam<std::string>("cross_section_data",
                                       "The name of the cross section file that Bolsig+ will use.");
  params.addRequiredParam<std::string>("boltzmann_input_file",
                                       "The name of the input file to Bolsig+.");
  params.addRequiredParam<std::vector<std::string>>("reaction_species", "The name of the species.");
  params.addRequiredParam<std::vector<std::string>>(
      "reaction_type", "The type of reaction for the corresponding reaction_species.");
  params.addRequiredParam<std::vector<int>>(
      "reaction_number",
      "An array containing the number of the reaction in the list. (e.g. 1, 3, 4)");
  params.addRequiredParam<int>("number_reactions",
                               "The number of reactions being computed by Bolsig+.");
  params.addParam<Real>("conversion_factor",
                        1.0,
                        "Units of rate coefficients output by Bolsig+ default to m^3/s. This will "
                        "be used to convert those values to your desired units.");
  params.addParam<bool>("output_table",
                        false,
                        "Whether or not the rate coefficients should be output as a table. If "
                        "False, single values are output.");
  params.addParam<std::string>("table_variable",
                               "The variable being used to tabulate rate coefficient data. "
                               "Options: reduced_field or electron_temperature.");
  params.addParam<int>(
      "n_steps",
      1,
      "Bolsig+ will be updated and run every n_steps. Default: 1 (runs every timestep).");
  params.addParam<Real>(
      "cutoff_time", -1.0, "If the simulation time is over this value, BOLSIG+ will not run.");
  return params;
}

std::fstream &
getLine(std::fstream & file, unsigned int num)
{
  file.seekg(std::ios::beg);
  for (MooseIndex(num) i = 0; i < num - 1; ++i)
  {
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  return file;
}

BoltzmannSolverScalar::BoltzmannSolverScalar(const InputParameters & parameters)
  : GeneralUserObject(parameters),
    _file_name(getParam<std::string>("boltzmann_input_file")),
    _nargs(coupledScalarComponents("mole_fractions")),
    _args(_nargs),
    _fractions_string(_nargs),
    _cross_sections(getParam<std::string>("cross_section_data")),
    _reduced_field(coupledScalarValue("reduced_field")),
    _plasma_density(coupledScalarValue("neutral_density")),
    _ionization_fraction(coupledScalarValue("ionization_fraction")),
    _reaction_species(getParam<std::vector<std::string>>("reaction_species")),
    _reaction_type(getParam<std::vector<std::string>>("reaction_type")),
    _output_table(getParam<bool>("output_table")),
    _table_variable(getParam<std::string>("table_variable")),
    _reaction_number(getParam<std::vector<int>>("reaction_number")),
    _num_reactions(getParam<int>("number_reactions")),
    _n_steps(getParam<int>("n_steps")),
    _cutoff_time(getParam<Real>("cutoff_time")),
    _conversion_factor(getParam<Real>("conversion_factor"))
{
  // First append the .dat file extension to the end of the input, output, and cross section files
  std::string output_file;

  _cross_sections = _cross_sections + ".dat";
  _output_file_name = _file_name + "_out.dat";
  _file_name = _file_name + ".dat";

  // Now edit the input file with cross section data
  std::string edit_command;
  edit_command = "sed -e \"9s/.*/" + _cross_sections + " \\/ File/\" -i \'\' " + _file_name;
  const char * command = edit_command.c_str();
  system(command);

  // Next the output file is named ("input_file_name_out")
  edit_command = "sed -e \"54s/.*/" + _output_file_name + " \\/   File /\" -i \'\' " + _file_name;
  command = edit_command.c_str();
  system(command);

  int line_counter;
  std::string line;
  for (MooseIndex(_nargs) i = 0; i < _nargs; ++i)
  {
    _args[i] = &coupledScalarValue("mole_fractions", i);
  }

  _timestep_number = 0;
  _bolsig_run = "./bolsigminus " + _file_name;
  // const char *command = _bolsig_run.c_str();

  // If there is an output table, we need to store the size of the array so the
  // program knows how many loops to take to store each rate coefficient
  if (_output_table)
  {
    if (_table_variable != "reduced_field" && _table_variable != "electron_temperature")
    {
      mooseError("Parameter table_variable must be either reduced_field or electron_temperature!");
    }
    line_counter = 0;
    int test_linenum = 0;
    std::fstream input_file(_file_name);
    while (getline(input_file, line))
    {

      line_counter++;
      if (line.find("/ Number") != std::string::npos)
      {
        test_linenum = line_counter;
        break;
      }
    }
    input_file.seekg(0);
    input_file.clear();
    getLine(input_file, test_linenum);
    input_file >> _table_number;
  }

  // _num_reactions = _reaction_number.size();
  // Now we find the line numbers in the output file
  _reaction_line.resize(_num_reactions); // Creates a vector of integers to store the line numbers
  _coefficient_interpolation.resize(_num_reactions);
  _rate_coefficient.resize(_num_reactions);
  if (_output_table)
  {
    _x_val.resize(_table_number);
    _electron_mobility.resize(_table_number);
    _electron_temperature.resize(_table_number);
    for (int i = 0; i < _num_reactions; ++i)
    {
      _rate_coefficient[i].resize(_table_number);
    }
  }
  else
  {
    for (int i = 0; i < _num_reactions; ++i)
    {
      _rate_coefficient[i].resize(1);
    }
    _x_val.resize(1);
    _electron_mobility.resize(1);
    _electron_temperature.resize(1);
  }

  // Need to include a better check. If file does not exist, run bolsig+ so that
  // it is created!
  // if (file)
  // {
  std::string current_reaction;
  // std::string line;
  // int line_counter;
  for (int i = 0; i < _num_reactions; ++i)
  {
    std::ifstream file(_output_file_name);
    line_counter = 0;
    current_reaction = _reaction_species[i] + "    " + _reaction_type[i];
    while (getline(file, line))
    {
      line_counter++;
      if (line.find(current_reaction) != std::string::npos)
      {
        // std::cout << line_counter << std::endl;
        // If a line number is found, we know that we can simply skip two lines
        // to get to the rate coefficient (Bolsig+ output files are very uniformly structured.)
        _reaction_line[i] = line_counter + 2;
      }
    }
    // file.seekg(0);
    // file.clear();
    file.close();
  }

  line_counter = 0;
  std::ifstream file(_output_file_name);
  while (getline(file, line))
  {
    line_counter++;
    if (line.find("Mobility *N") != std::string::npos)
    {
      // std::cout << line << std::endl;
      // mooseError("EXIT");
      _mobility_line = line_counter + 1;
      break;
    }
  }
  // file.close();

  line_counter = 0;
  while (getline(file, line))
  {
    line_counter++;
    if (line.find("Diffusion coefficient *N ") != std::string::npos)
    {
      _diffusivity_line = line_counter + 1;
      break;
    }
  }

  file.seekg(0);
  file.clear();
  line_counter = 0;
  while (getline(file, line))
  {
    line_counter++;
    if (line.find("Mean energy (eV)") != std::string::npos)
    {
      _temperature_line = line_counter + 1;
      break;
    }
  }
  file.close();

  // Find the number of runs under RUNSERIES (valid if data_table set to true)
  // file.seekg(0);
  // file.clear();
  //
  // }
  // else
  // {
  //   mooseError("Could not open BOLSIG+ output file! Make sure it exists.");
  // }
  // file.close();
}

Real
BoltzmannSolverScalar::test(const int i) const
{
  return _rate_coefficient[i][0] * _conversion_factor;
}

Real
BoltzmannSolverScalar::electron_mobility() const
{
  return _electron_mobility[0];
}

Real
BoltzmannSolverScalar::electron_temperature() const
{
  return _electron_temperature[0];
}

Real
BoltzmannSolverScalar::coefficient_sample(const int i, const Real sampler) const
{
  return _coefficient_interpolation[i].sample(sampler);
}

Real
BoltzmannSolverScalar::electron_temperature_sample(const Real sampler) const
{
  return _temperature_interpolation.sample(sampler);
  // return _mobility_interpolation.sample(sampler);
}

Real
BoltzmannSolverScalar::electron_mobility_sample(const Real sampler) const
{
  return _mobility_interpolation.sample(sampler);
}

void
BoltzmannSolverScalar::initialize()
{
  // Here we can write the input file based on input parameters
  // Required input: gas composition fractions, gas temperature

  // std::cout << std::to_string((*_args[1])[0]) << std::endl;
  // To rewrite file, we can use a bash command (using system()):
  // sed -e "34s/.*/0.23 0.77  \/ Gas composition fraction/" -i ''  temp_in.dat
  //   line # ^     [       ] <- replacement string
  // If n steps have passed, write mole fractions and reduced field value into input file
  if (_t <= _cutoff_time)
  {
    if (_timestep_number == _n_steps || _timestep_number == 0)
    {
      std::string edit_command;
      edit_command = "sed -e \"34s/.*/";
      // std::cout << coupledScalarValue("mole_fractions", 0) << std::endl;
      // For each variable we add both the value (converted to a string) and a following space
      // character.
      for (unsigned int i = 0; i < _nargs; ++i)
      {
        _fractions_string[i] << std::setprecision(10) << (*_args[i])[0];
        // std::cout << _fractions_string[i].str() << std::endl;
        edit_command = edit_command + _fractions_string[i].str() + " ";

        _fractions_string[i].str("");
      }
      // edit_command = edit_command + "\\/ Gas composition fraction/\" -i \'\' temp_in.dat";
      edit_command = edit_command + "\\/ Gas composition fraction/\" -i \'\' " + _file_name;

      // Real test1, test2;
      // test1 = 0.3;
      // test2 = 0.7;
      // edit_command = "sed -e \"34s/.*/"+std::to_string(test1)+" "+std::to_string(test2)+" \\/ Gas
      // composition fraction/\" -i \'\' temp_in.dat";
      const char * command = edit_command.c_str();

      system(command);

      // Now the input file is edited with updated molar fractions!

      // Update the reduced field line:
      if ((_output_table && _table_variable != "reduced_field") || !_output_table)
      {
        _field_string << (_reduced_field[0] * 1e21);
        // edit_command = "sed -e \"14s/.*/"+_field_string.str()+" \\/ Reduced field (Td)/\" -i \'\'
        // temp_in.dat";
        edit_command = "sed -e \"14s/.*/" + _field_string.str() +
                       " \\/ Reduced field (Td)/\" -i \'\' " + _file_name;
        _field_string.str("");
        // std::cout << edit_command << std::endl;
        command = edit_command.c_str();
        system(command);
      }

      // Update the ionization fraction line
      _field_string << std::setprecision(8) << (_ionization_fraction[0]);
      // edit_command = "sed -e \"20s/.*/"+_field_string.str()+" \\/ Ionization degree/\" -i \'\'
      // temp_in.dat";
      edit_command = "sed -e \"20s/.*/" + _field_string.str() +
                     " \\/ Ionization degree/\" -i \'\' " + _file_name;
      _field_string.str("");
      command = edit_command.c_str();
      system(command);
    }
  }
}

void
BoltzmannSolverScalar::execute()
{
  // Run BOLSIG+
  // system("./bolsigminus example3.dat");
  if (_t <= _cutoff_time)
  {
    if (_timestep_number == _n_steps || _timestep_number == 0)
    {

      _timestep_number = 1;

      const char * command = _bolsig_run.c_str();
      std::cout << "\nRunning BOLSIG+..." << std::endl;
      system(command);
      std::cout << "DONE" << std::endl;
      std::fstream file(_output_file_name);

      if (_output_table)
      {
        for (int i = 0; i < _num_reactions; ++i)
        {
          getLine(file, _reaction_line[i]);
          for (int j = 0; j < _table_number; ++j)
          {
            file >> _x_val[j] >> _rate_coefficient[i][j];
            _rate_coefficient[i][j] = _rate_coefficient[i][j] * _conversion_factor;
          }

          _coefficient_interpolation[i].setData(_x_val, _rate_coefficient[i]);
        }

        // Electron Temperature
        getLine(file, _temperature_line);
        for (int j = 0; j < _table_number; ++j)
        {
          file >> _tempstore >> _electron_temperature[j];
        }

        // Electron Mobility
        getLine(file, _mobility_line);
        for (int j = 0; j < _table_number; ++j)
        {
          // Note that BOLSIG+ outputs mobility as a mobility * N.
          // Here the value is converted back to mobility alone.
          // _conversion_factor simply converts to the desired units. Defaults to 1.0.
          file >> _tempstore >> _electron_mobility[j];
          _electron_mobility[j] = _electron_mobility[j] / (_plasma_density[0] * _conversion_factor);
        }

        // Now we interpolate the results to output a "table"
        _temperature_interpolation.setData(_x_val, _electron_temperature);
        _mobility_interpolation.setData(_x_val, _electron_mobility);
      }
      else
      {
        for (int i = 0; i < _num_reactions; ++i)
        {
          getLine(file, _reaction_line[i]);
          file >> _tempstore >> _rate_coefficient[i][0];
          // if (_rate_coefficient[i] == 0.0)
          //   mooseError("Zero rate coefficient");
        }

        // Electron temperature
        getLine(file, _temperature_line);
        file >> _tempstore >> _electron_temperature[0];

        // Electron mobility
        getLine(file, _mobility_line);
        file >> _tempstore >> _electron_mobility[0];
        _electron_mobility[0] = _electron_mobility[0] / (_plasma_density[0] * _conversion_factor);
      }
    }
    else
    {
      _timestep_number = _timestep_number + 1;
    }
    // getLine(file, 113);

    // file >> _x_val >> _rate_coefficient;
    // Now we will fit everything into data tables (automatically...difficult.)
    // Not sure how to do this easily. Ugh.

    // std::cout << "Tabulating rate coefficients..." << std::endl;
  }
}

void
BoltzmannSolverScalar::finalize()
{
}
