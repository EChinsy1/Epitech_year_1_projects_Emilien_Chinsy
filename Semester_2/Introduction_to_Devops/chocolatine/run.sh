#!/bin/bash
# Specify folder where you can find sources , on your local machine
SOURCE_FOLDER=/home/gfaim/projects_for_school/devops/chocolatine_bs
# Specify destination folder to mount your project into docker
DEST_FOLDER=/home/ubuntu/
docker run --rm -v "$SOURCE_FOLDER:$DEST_FOLDER" -it epitechcontent/epitest-docker /bin/bash -c 'su - ubuntu'
