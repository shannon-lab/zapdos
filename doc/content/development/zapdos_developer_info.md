# Zapdos Developer Information

This page is meant for Zapdos developers and will change over time as development practices and
processes change - please refer back to this page regularly. If MOOSE user and developer information
is desired, please refer to the [moose_developer_info.md] page.

## Update and Build a New Docker Container

!style halign=left
The Zapdos docker container image should be updated whenever Zapdos source code or submodules (CRANE,
Squirrel, or MOOSE) are updated and those changes are merged into the master branch. Whenever the
MOOSE submodule is updated, in particular, the submodule git commit hash must be copied and entered
into the `Dockerfile` so that the proper MOOSE docker image can be used with the Zapdos image.

To build a new docker container, first fetch the most up-to-date version of the Zapdos master branch.
Assuming that Zapdos is stored in `~/projects/` and that your `upstream` remote is referencing
[shannon-lab/zapdos](https://github.com/shannon-lab/zapdos.git):

```bash
cd ~/projects/zapdos
git fetch upstream
git checkout master
git rebase upstream/master
```

Once your local master branch is up-to-date, the `build_socker.sh` script can be used to create two
new images, one tagged with the most recent git commit hash for the master branch and one tagged
`latest`. The script has two parameters:

- `ZAPDOS_DIR` - the current Zapdos directory (set in the environment, or on the command line when
  the script is run). This parameter is required!
- `PUSH` - a boolean value that sets whether the built packages should be pushed to the `shannonlab/zapdos`
  Docker Hub repository when the build is completed (defaults to `0`)

Example usage of the script is outlined as follows. First, start the script from the Zapdos directory:

```bash
cd ~/projects/zapdos
ZAPDOS_DIR=$(pwd) scripts/build_docker.sh
```

In this case, the docker images will remain local and will not be pushed to Docker Hub (`PUSH=0`).
Example output for this command is shown below:

```bash
% ZAPDOS_DIR=$(pwd) scripts/build_docker.sh
[+] Building 0.5s (8/8) FINISHED
 => [internal] load build definition from Dockerfile                                                                                                     0.0s
 => => transferring dockerfile: 44B                                                                                                                      0.0s
 => [internal] load .dockerignore                                                                                                                        0.0s
 => => transferring context: 2B                                                                                                                          0.0s
 => [internal] load metadata for docker.io/idaholab/moose:d73fc06368c8b33549cd1ec86f8863920789a878                                                       0.4s
 => [1/4] FROM docker.io/idaholab/moose:d73fc06368c8b33549cd1ec86f8863920789a878@sha256:89d12bcc14b06e71d5f0e267412b718dfe1d63c984b2bb67dcc1b76f0f995cc  0.0s
pick 79e7daa2 Add docker build and upload script
 => CACHED [2/4] WORKDIR /opt                                                                                                                            0.0s
 => CACHED [3/4] RUN git clone -b master https://github.com/shannon-lab/zapdos.git ; cd zapdos ; git submodule update --init crane squirrel ; make -j $  0.0s
 => CACHED [4/4] WORKDIR /opt/zapdos                                                                                                                     0.0s
 => exporting to image                                                                                                                                   0.0s
 => => exporting layers                                                                                                                                  0.0s
 => => writing image sha256:26565cd5c868ecd702d727fa9c2a95caf24d9741e629d1cc3f39261b9b592570                                                             0.0s
 => => naming to docker.io/shannonlab/zapdos:2c4a214d4d55106ac6c8c9058e3b224a46ba416d                                                                    0.0s

Use 'docker scan' to run Snyk tests against images to find vulnerabilities and learn how to fix them

INFO: Push to Docker Hub disabled. If desired in the future, run this script
      with PUSH=1 in your environment or run the following two commands:

      docker push shannonlab/zapdos:2c4a214d4d55106ac6c8c9058e3b224a46ba416d
      docker push shannonlab/zapdos:latest
```




