# Getting Started

## Step One: Install Conda MOOSE Environment

!style halign=left
In order to install Zapdos, the MOOSE developer environment must be installed. The
installation procedure depends on your operating system, so click on the MOOSE
website link below that corresponds to your operation system/platform and follow
the instructions to the conda installation step named "Cloning MOOSE". Then,
return to this page and continue with Step Two.

- [Linux and MacOS](https://mooseframework.inl.gov/getting_started/installation/conda.html)
- [Windows 10 (experimental)](https://mooseframework.inl.gov/getting_started/installation/windows10.html)

Advanced manual installation instructions for this environment are available
[via the MOOSE website](https://mooseframework.inl.gov/getting_started/installation/index.html).

If an error or other issue is experienced while using the conda environment,
please see [the MOOSE troubleshooting guide for Conda](https://mooseframework.inl.gov/help/troubleshooting.html#condaissues)

## Step Two: Clone Zapdos

!style halign=left
Zapdos is hosted on [GitHub](https://github.com/shannon-lab/zapdos), and should
be cloned directly from there using [git](https://git-scm.com/). As in the MOOSE
directions, it is recommended that users create a directory named "projects" to
put all of your MOOSE-related work.

To clone Zapdos, run the following commands in Terminal:

```bash
mkdir ~/projects
cd ~/projects
git clone https://github.com/shannon-lab/zapdos.git
cd zapdos
git checkout master
```

## Step Three: Build and Test Zapdos

!style halign=left
To compile Zapdos, first make sure that the conda MOOSE environment is activated
(*and be sure to do this any time that a new Terminal window is opened*):

```bash
conda activate moose
```

Then navigate to the Zapdos clone directory and download the MOOSE submodule:

```bash
cd ~/projects/zapdos
git submodule update --init squirrel crane moose
```

!alert note
The copy of MOOSE provided with Zapdos has been fully tested against the current
Zapdos version, and is guaranteed to work with all current Zapdos tests.

Once all dependencies have been downloaded, Zapdos can be compiled and tested:

```bash
make -j8
./run_tests -j8
```

If Zapdos is working correctly, all active tests will pass. This indicates that
Zapdos is ready to be used and further developed.

## Updating Zapdos

!style halign=left
To update Zapdos, it is recommended to use fetch and rebase:

```bash
cd ~/projects/zapdos
git fetch origin
git rebase origin/master
```

## Alternate Installation: Docker

Zapdos is also available a container hosted on Docker Hub in the repository [shannonlab/zapdos](https://hub.docker.com/r/shannonlab/zapdos) for Ubuntu 20.04. The tag "latest" is kept current with the master branch of the Zapdos repository, and the other tags are commit hashes in line with git commit hashes for prior Zapdos updates. The Docker image contains a prebuilt copy of Zapdos, installable with one command (once Docker is installed on the host machine):

```bash
docker run -ti shannonlab/zapdos:latest
```

### Zapdos Docker Container Minimum System Requirements

- Some flavor of Linux, MacOS, or Windows with [Docker](https://www.docker.com) installed
- Memory: 16GBs (debug builds)
- Processor: 64-bit x86 or ARM64 (Apple Silicon)
- Disk: 6GB (image size)

## Troubleshooting

!style halign=left
If issues are experienced in installation and testing, several resources
are available:

- [Zapdos Discussion Forum](https://github.com/shannon-lab/zapdos/discussions)
- [MOOSE FAQ page for common MOOSE issues](https://mooseframework.inl.gov/help/faq/index.html)
- [MOOSE Discussion Forum](https://github.com/idaholab/moose/discussions)

## What next?

!style halign=left
With installation and testing complete, proceed to [using_zapdos.md].
