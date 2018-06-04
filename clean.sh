#!/bin/bash
find src/ | grep '[^a-zA-Z0-9_\./-]' | xargs rm -rf

