#include "controller.h"

using namespace s21;

int Controller::processInputData(string& fileName) {
  return parser_.processInputData(fileName);
}

void Controller::verticesToArray() { return parser_.verticesToArray(); }

void Controller::facetsToArray() { return parser_.facetsToArray(); }

void Controller::translation(double x, double y, double z) {
  return transform_.translation(x, y, z);
}

void Controller::rotation(double angle) { return transform_.rotation(angle); }

void Controller::scalling(double zoom) { return transform_.scalling(zoom); }

void Controller::printMatrix() { return parser_.printMatrix(); }