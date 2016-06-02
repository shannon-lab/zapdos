Zapdos
=====

Free (in all senses of the word) and open source software for modelling atmospheric plasmas using finite elements.
This application is built on top of the MOOSE framework, which can be found at [http://mooseframework.org](http://mooseframework.org)

The best documentation so far for this project is in [this thesis chapter.](http://169.229.198.106/ZapdosChapter.pdf)

**Instructions for installing Zapdos:**

<ol>
  <li>Follow the <a href="http://mooseframework.org/getting-started/">getting started instructions</a> for installing the MOOSE and libmesh packages that Zapdos depends on.</li>
  <li>After installing MOOSE and libmesh, execute the following commands</li>
  <ul>
    <li><code>cd ~/projects</code></li>
    <li><code>git clone https://github.com/shannon-lab/zapdos</code></li>
    <li><code>cd zapdos</code></li>
    <li><code>make -j4</code> or <code>make -j8</code> depending on the number of processors on your computer</li>
  </ul>
  <li>Open your <code>.bashrc</code> file with your favorite text editor. (I recommend <b>emacs</b> of course.) Add the following line to your <code>.bashrc</code> file:</li>
  <ul>
    <li><code>export ZAPDIR=~/projects/zapdos</code></li>
  </ul>
  <li>You should now be able to run input files using the <code>zapdos-opt</code> executable in the <code>~/projects/zapdos</code> directory. A great example input file is <code>mean_en.i</code> in <code>~/projects/zapdos/problems</code>. I typically run an input file like <code>mean_en.i</code> using the following command:</li>
  <ul>
    <li><code>cd ~/projects/zapdos/problems; ../zapdos-opt -i mean_en.i --no-color 2>&1 | tee log.txt</code></li>  
    <li>The above command will parse information of the iterative solution process to both the console and to the log file <code>log.txt</code></li>  
    <li>The above command will also create an output file named <code>mean_en_out.e</code> containing all the solution variable values. These results are best viewed using a visualization tool like <b>Paraview</b>, downloadable <a href="http://www.paraview.org/download/">here</a></li>
  </ul>  
</ol>

Please do not hesitate to contact me if you have any questions about using or contribution to this software.

Email: <adlinds3@ncsu.edu>
