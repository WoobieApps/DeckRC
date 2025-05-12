#!/bin/bash
rm -rf .flatpak-builder/rofiles
flatpak run org.flatpak.Builder \
    --force-clean \
    --user \
    --install \
    build \
    org.deckrc.remotectrl.yaml