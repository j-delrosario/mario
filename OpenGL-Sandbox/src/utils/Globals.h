/**
 * @file
 * @brief defines functions, macros, and constants dealing with global
 * variables and singleton objects.
 */
#ifndef GLOBALS_H
#define GLOBALS_H

#include "ResourceManager.h"
#include "Singleton.h"
#include "Animation.h"

#define RESOURCE_MANAGER (Singleton<ResourceManager>::GetInstance())

void CreateGlobals();

void DestroyGlobals();

#endif