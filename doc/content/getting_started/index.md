# Getting Started

## Install MOOSE

First you will need to install the MOOSE Framework. To do this, proceed to the
[MOOSE Getting Started pages](https://mooseframework.inl.gov/getting_started/index.html). After
successfully installing MOOSE, return to this page to continue.

## Test MOOSE

To test MOOSE, do the following:

```bash
cd ~/projects/moose/test
make -j4
./run_tests -j4
```

!alert note
You can replace `-j4` with `-j` plus the number of cores your computer has available for faster
build performance.

## Build and Test Zapdos

To build Zapdos, do the following:

```bash
cd ~/projects/zapdos
make -j4
./run_tests -j4
```

If Zapdos is working correctly, all active tests will pass. This indicates that Zapdos is ready to
be used and further developed.

## Troubleshooting

Please see the [MOOSE FAQ page](https://www.mooseframework.org/help/faq.html) for general
troubleshooting information for the framework. If your issue is not listed among the FAQs, please
refer to the [Zapdos Mailing List](https://groups.google.com/forum/#!forum/zapdos-users) or the
[MOOSE Mailing List](https://groups.google.com/forum/#!forum/moose-users).
