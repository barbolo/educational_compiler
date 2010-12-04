#ifndef SYNTATIC_H
#define SYNTATIC_H

/*
 *  sintatic.h
 *  compiler
 */

#include "analyser.h"
#include "ape.h"
#include "actions.h"

void run_sintatic();

int was_correctly_parsed();

int semantic_error;

#endif