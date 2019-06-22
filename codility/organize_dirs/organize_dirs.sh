#! /bin/bash

set -e

# Tools
RM="rm -f"
MV="mv -bf"     # Save a backup if the file exists on the destination
MKDIR="mkdir -p"

# Moved files
MUSIC_FILTER=("*.mp3" "*.flac")
MUSIC_DIR="music"

IMAGES_FILTER=("*.jpg" "*.png")
IMAGES_DIR="images"

VIDEO_FILTER=("*.avi" "*.mov")
VIDEO_DIR="videos"

# Removed files
REMOVED_FILTER="*.log"

move_files () {
    DIR=$1
    shift
    FILTER=("${@}")
    ${MKDIR} ${DIR}
    for subfilter in ${FILTER[@]}; do
        ${MV} ${subfilter} ${DIR}
    done
}

move_files ${MUSIC_DIR} "${MUSIC_FILTER[@]}"
move_files ${IMAGES_DIR} ${IMAGES_FILTER}
move_files ${VIDEO_DIR} ${VIDEO_FILTER}
${RM} ${REMOVED_FILTER}
