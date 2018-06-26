#!/bin/bash
bash <(curl -sL https://raw.githubusercontent.com/nrobinson2000/po/master/ci/ci-install)
po lib clean . -f &> /dev/null
yes "no" | po lib setup # change to "yes" to prefer libraries from GitHub
po photon build
