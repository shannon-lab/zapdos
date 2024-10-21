# CRANE Tutorial
Repository for the source code and files of the CRANE tutorial, given as part of the GEC 2018 MOOSE Workshop.


## How To Build
1) Download and install a LaTeX distribution (TeX Live or MikTeX are good choices for Windows, MacTeX for MacOS, and many more exist...).
2) If you want to build the presentation using a visual environment, ensure that your distribution came with one or download one (**NOTE** TexStudio seems to be the best IDE to build the presentation with, as others seem to produce errors pertaining to interpretation of tabs/spaces - a quirk of the internal text editors in these programs).
3) Build the document:

   * If you are using a visual environment, refer to the build instructions that come with that program. See the NOTE below - it also applies to builds using editors.

   * If you are using the terminal (in Linux or MacOS) or command prompt (Windows), use the following command in the directory where the workshop .tex file is located:

      ```
      pdflatex -synctex=1 -interaction=nonstopmode "keniley_crane_aps-gec".tex
      ```

      **NOTE:** Because the LaTeX compiler requires cross-referencing information to build the table of contents, you must run this command twice to ensure that the table of contents is built and visible for presentation navigation!
