#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "util.h"

// Figure out which child octant a particle belongs to. Returns a
// number from 0 to 7, inclusive.
//
// 'l' is the edge length of space.
int octant(struct vec3 corner, double l, const struct particle* p) {
  if (p->pos.x >= corner.x+l/2) {
    if (p->pos.y >= corner.y+l/2) {
      if (p->pos.z >= corner.z+l/2) {
        return 0;
      } else {
        return 1;
      }
    } else {
      if (p->pos.z >= corner.z+l/2) {
        return 2;
      } else {
        return 3;
      }
    }
  } else {
    if (p->pos.y >= corner.y+l/2) {
      if (p->pos.z >= corner.z+l/2) {
        return 4;
      } else {
        return 5;
      }
    } else {
      if (p->pos.z >= corner.z+l/2) {
        return 6;
      } else {
        return 7;
      }
    }
  }
}

// Given the index of a child octant (0-7), place in *ox/*oy/*oz the
// normalized corner coordinate.
void octant_offset(int j, double* ox, double* oy, double* oz) {
  switch (j) {
  case 0:
    *ox = 0.5;
    *oy = 0.5;
    *oz = 0.5;
    break;
  case 1:
    *ox = 0.5;
    *oy = 0.5;
    *oz = 0.0;
    break;
  case 2:
    *ox = 0.5;
    *oy = 0.0;
    *oz = 0.5;
    break;
  case 3:
    *ox = 0.5;
    *oy = 0.0;
    *oz = 0.0;
    break;
  case 4:
    *ox = 0.0;
    *oy = 0.5;
    *oz = 0.5;
    break;
  case 5:
    *ox = 0.0;
    *oy = 0.5;
    *oz = 0.0;
    break;
  case 6:
    *ox = 0.0;
    *oy = 0.0;
    *oz = 0.5;
    break;
  case 7:
    *ox = 0.0;
    *oy = 0.0;
    *oz = 0.0;
    break;
  }
}

// You do not need to modify this definition.
struct bh_node {
  bool internal; // False when external.

  struct vec3 corner;
  double l; // Edge length of space.

  // Fields for external nodes.
  int particle; // Index of particle in particle array; -1 if none.

  // Fields for internal nodes. Only have sensible values when
  // 'internal' is true.
  struct vec3 com; // Center of mass.
  double mass; // Total mass.
  struct bh_node* children[8];
};

// Turn an external node into an internal node containing no
// particles, and with 8 external node children.
void bh_mk_internal(struct bh_node* bh) {
  // Must not already be external.
  assert(!bh->internal);

  // We must set necessary fields and then allocate (and properly
  // initialise) our children.

  assert(0); // TODO
}

// Insert particle 'p' (which must be a valid index in 'ps') into our octree.
void bh_insert(struct bh_node* bh, struct particle* ps, int p) {
  if (bh->internal) {
    // This is an internal node. Recursively insert the particle in
    // the appropriate child (computed with octant()), then update the
    // centre of mass.

    assert(0); // TODO
  } else {
    // This is an external node.
    if (bh->particle == -1) {
      // This is an external node currently with no particle, so we
      // can just insert the new particle.

      assert(0); // TODO
    } else {
      // This is an external node that already has a particle. We must
      // convert it into an internal node with initially zero mass,
      // and then insert both the new particle *and* the one it
      // previously contained, using recursive calls to bh_insert.

      assert(0); // TODO
    }
  }
}

// Free all memory used for the tree.
void bh_free(struct bh_node* bh) {
  assert(0); // TODO
}

// Compute the accel acting on particle 'p'.  Increments *ax, *ay, and *az.
void bh_accel(double theta, struct bh_node* bh,
              struct particle* ps, int p,
              struct vec3 *a) {
  if (bh->internal) {
    assert(0); // TODO
  } else if (bh->particle != -1 && bh->particle != p) {
    assert(0); // TODO
  }
}

// Create a new octree that spans a space with the provided minimum
// and maximum coordinates.
struct bh_node* bh_new(double min_coord, double max_coord) {
  struct bh_node* bh = malloc(sizeof(struct bh_node));
  bh->x = min_coord;
  bh->y = min_coord;
  bh->z = min_coord;
  bh->l = max_coord-min_coord;
  bh->internal = false;
  bh->particle = -1;
  return bh;
}

// Barnes-Hut N-body simulation.
void nbody(int n, struct particle *ps, int steps, double theta) {
  for(int s = 0; s < steps; s++) {
    // For each iteration, construct the octree (first you must
    // determine the minimum and maximum coordinates), then compute
    // accelerations and update velocities, then update positions.

    assert(0); // TODO
  }
}

int main(int argc, char** argv) {
  int steps = 1;
  double theta = 0.5;
  if (argc < 3) {
    printf("Usage: \n");
    printf("%s <input> <output> [steps]\n", argv[0]);
    return 1;
  }
  if (argc > 3) {
    steps = atoi(argv[3]);
  }
  if (argc > 4) {
    theta = atof(argv[4]);
  }

  int32_t n;
  struct particle *ps = read_particles(argv[1], &n);

  double bef = seconds();
  nbody(n, ps, steps, theta);
  double aft = seconds();
  printf("%f\n", aft-bef);
  write_particles(argv[2], n, ps);
  free(ps);
}
