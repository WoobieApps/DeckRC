#!/bin/bash
set -e  # Exit on any error

# Unmount any rofiles-fuse mount points
ROFILES_DIR=".flatpak-builder/rofiles"

if [ -d "$ROFILES_DIR" ]; then
    for mnt in "$ROFILES_DIR"/rofiles-*; do
        if mountpoint -q "$mnt"; then
            echo "Unmounting $mnt"
            fusermount -u "$mnt" || umount "$mnt"
        fi
    done
    echo "Removing $ROFILES_DIR"
    rm -rf "$ROFILES_DIR"
fi

# Run the flatpak-builder
flatpak run org.flatpak.Builder \
    --force-clean \
    --user \
    --install \
    build \
    org.deckrc.remotectrl.yaml
