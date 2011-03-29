#!/usr/bin/env python
from random import shuffle
from ants import *
from functions import *

LAND = -1
FOOD = -2
WATER = -3
CONFLICT = -4
UNSEEN = -5
PLAYERS = ('1', '2', '3', '4')

class BroBot():
    def do_turn(self, ants):
        destinations = []
        for a_row, a_col in ants.my_ants():
            targets = ants.food() + [(row, col) for (row, col), owner in ants.enemy_ants()]
            # find closest food or enemy ant
            closest_target = None
            closest_distance = 999999
            for t_row, t_col in targets:
                dist = ants.distance(a_row, a_col, t_row, t_col)
                if dist < closest_distance:
                    closest_distance = dist
                    closest_target = (t_row, t_col)
            if closest_target == None:
                # no target found, mark ant as not moving so we don't run into it
                destinations.append((a_row, a_col))
                continue
            directions = ants.direction(a_row, a_col, closest_target[0], closest_target[1])
            shuffle(directions)
            for direction in directions:
                n_row, n_col = ants.destination(a_row, a_col, direction)
                if ants.unoccupied(n_row, n_col) and not (n_row, n_col) in destinations:
                    destinations.append((n_row, n_col))
                    ants.issue_order((a_row, a_col, direction))
                    break
            else:
                # mark ant as not moving so we don't run into it
                destinations.append((a_row, a_col))

class MyMap():
  map = []
  def __init__(self)
    self.coverage = 0.0
    self.symetric = 0

class MyArea():
  def __init__(self, x, y, size)
    self.x = x
    self.y = y
    self.size = size
    self.dangerous = False
    self.enemy = False
    self.food = False
    self.unknown = False

class MyAnt():
  ACTIONS = ('discover', 'attack', 'run', 'stop')
  def __init__(self, safe)
    self.x = x
    self.y = y
    self.direction = (0, 0)
    self.safe = True
  def safe(self, safe)
    self.safe = safe
  def setAction(self, action, priority)
    self.safe = safe
    self.priority = priority

class MyEnemy():
  def __init__(self)
    self.aggresive = False
    self.won = False
    self.freeze = False
    self.stupid = False


## Main Execution Code ##
if __name__ == '__main__':
    try:
        import psyco
        psyco.full()
    except ImportError:
        pass
    try:
        Ants.run(BroBot())
    except KeyboardInterrupt:
        print('ctrl-c, leaving ...')

