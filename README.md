Zapdos
=====

Free (in all senses of the word) and open source software for modelling atmospheric plasmas using finite elements.
This application is built on top of the MOOSE framework, which can be found at [http://mooseframework.org](http://mooseframework.org)

The best documentation so far for this project is in [this thesis chapter.](http://169.229.198.106/ZapdosChapter.pdf)

**Instructions for installing Zapdos:**

<ol>
  <li>Follow the <a href="http://mooseframework.org/getting-started/">getting started instructions</a> for installing the MOOSE and libmesh packages that Zapdos depends on.</li>
  <li>After installing libmesh and MOOSE and performing the tests in MOOSE's <code>test</code> directory, execute the following commands</li>
  <ul>
    <li><code>cd ~/projects</code></li>
    <li><code>git clone https://github.com/shannon-lab/zapdos</code></li>
    <li><code>cd zapdos</code></li>
    <li><code>make -jn</code>, substituting the character 'n' with the integer number of processor on your computer, e.g. perform <code>make -j4</code> if you have 4 processors</li>
  </ul>
  <li>Open your <code>.bashrc</code> file with your favorite text editor. (I recommend <b>emacs</b> of course.) Add the following line to your <code>.bashrc</code> file:</li>
  <ul>
    <li><code>export ZAPDIR=~/projects/zapdos</code></li>
  </ul>
  <li>To make sure the installation is working correct, execute <code>run_tests -jn</code>, again substituting 'n' with your number of processors. All tests should pass with 'OK'
  <li>If everything checks out, you should now be able to run input files using the <code>zapdos-opt</code> executable in the <code>~/projects/zapdos</code> directory. A great example input file is <code>mean_en.i</code> in <code>~/projects/zapdos/problems</code>. I typically run an input file like <code>mean_en.i</code> using the following command:</li>
  <ul>
    <li><code>cd ~/projects/zapdos/problems; ../zapdos-opt -i mean_en.i --no-color 2>&1 | tee log.txt</code></li>
    <li>The above command will parse information of the iterative solution process to both the console and to the log file <code>log.txt</code></li>
    <li>The above command will also create an output file named <code>mean_en_out.e</code> containing all the solution variable values. These results are best viewed using a visualization tool like <b>Paraview</b>, downloadable <a href="http://www.paraview.org/download/">here</a></li>
  </ul>
</ol>

Please do not hesitate to contact me if you have any questions about using or contributing to this software.

Email: <adlinds3@ncsu.edu>
