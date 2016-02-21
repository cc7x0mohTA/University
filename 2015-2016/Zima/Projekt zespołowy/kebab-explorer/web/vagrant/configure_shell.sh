#!/bin/bash

# Convenient shell aliases
BASHRC="${HOME}/.bashrc"
{
  echo;
  echo 'export PS1="[\u\[\033[1;31m\]@\[\033[0m\]\h]\[\033[1;31m\]:\[\033[0m\]<\w>\[\033[1;31m\]\$ \[\033[0m\]"';
  echo;
  echo "alias la='ls -lahGF'";
  echo;
} >> ${BASHRC}
