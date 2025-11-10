#!/bin/bash
nm minishell | grep U > ch.txt
awk 'allowfunctions.txt {print}' ch.txt
