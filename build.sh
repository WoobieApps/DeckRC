#!/bin/bash
flatpak run org.flatpak.Builder \
    --force-clean \
    --user \
    build \
    org.deckrc.remotectrl.yaml