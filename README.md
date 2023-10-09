# Flocking Simulation

This application generates a visualization of emergent collective behavior by simulating a flock of birds on openFrameworks in C++. Flocking is simulated with the self-propelled particles model of [eqs. 1 and 2](#eqs), a modified version of the one described in [ref. 1](#ref). Such particles are also known as _boids_.

https://github.com/ebolduc37/flocking-sim/assets/44382376/46d41d28-8490-43cc-9ef7-f1d97bed97c9

The particles evolve in a system that has periodic boundary conditions such that the unit cell is a cube, which we call the _simulation box_. Each particle moves according to [eqs. 1 and 2](#eqs). They interact with at most a fixed number of their closest neighbors and are subject to an alignment force, a cohesion force, and noise. All model parameters are initialized according to [ref. 1](#ref).

The cohesion force is formulated from a distance-dependent force between interacting neighbors according to [eqs. 3, 4, and 5](#eqs). Interacting neighbors are connected by a line: a red line indicates that there is hard-core repulsion following [eq. 3](#eqs); a blue line indicates that their distance is near an "equilibrium" preferred distance and that the attraction-repulsion force is close to zero following [eq. 4](#eqs); and a green line indicates that the force is constant following [eq. 5](#eqs).

Additionally, the user can change the interaction range and noise strength while the simulation is running.

## Commands

These commands can be used while the simulation is running to change certain aspects in real-time.

| Key                                                         | Effect                                  |
| :---------------------------------------------------------: | --------------------------------------- |
| <code>UP</code>/<code>DOWN</code>                           | Change the noise strength               |
| <code>LEFT</code>/<code>RIGHT</code>                        | Change the interaction range            |
| <code>P</code>                                              | Change the look of the simulation       |
| <code>R</code>                                              | Randomize the position of all particles |
| <code>W</code>/<code>A</code>/<code>S</code>/<code>D</code> | Rotate the simulation box               |
| <code>Q</code>/<code>E</code>                               | Zoom in/out                             |
| <code>SPACEBAR</code>                                       | Play/pause the simulation               |
| <code>ESC</code>                                            | Exit the simulation                     |

## Setup Variables

These parameters are initialized in the code before running the simulation to control the structure and outcome.

### Simulation Variables

These parameters control the scope of the simulation.

| Variable               | Description               |
| :--------------------: | ------------------------- |
| <code>NUM_BOIDS</code> | Total number of particles |
| <code>LENGTH</code>    | Simulation box length     |

### Visualization Variables

These variables control the visualization of the simulation in the output window, such that one frame corresponds to one iteration of the self-propelled particles model of [eqs. 1 and 2](#eqs).

| Variable                 | Description                                |
| :----------------------: | ------------------------------------------ |
| <code>FPS</code>         | Frames per second                          |
| <code>CAM_STEP</code>    | Camera position displacement per frame     |
| <code>CAM_POS_INI</code> | Initial camera position                    |
| <code>SHOW_INFO</code>   | Show/hide information in the output window |
| <code>SHOW_COMM</code>   | Show/hide commands in the output window    |

### Data Capture Variables

These variables control data collection.

| Variable               | Description                     |
| :--------------------: | ------------------------------- |
| <code>SAVE</code>      | Save all frames as .jpg files   |
| <code>TIME</code>      | Simulation runtime when saving  |
| <code>FILE_NAME</code> | File name prefix for all frames |
| <code>DIR</code>       | Directory name to save in       |

## Self-Propelled Particle Model <a id="eqs"/></a>

We consider the self-propelled particles model described in [ref. 1](#ref) and introduce a parameter modulating the noise strength. Each particle moves with vector velocity $\vec{v}_i(t)$ according to the following equations:

```math
\begin{gather}
\vec{v}_i(t+1) = v_0 \Theta \left[ \vec{f}_\alpha(t) + \vec{f}_\beta(t) + \vec{f}_\gamma(t) \right] \tag{1} \\
\vec{x}_i(t+1) = \vec{x}_i(t) + \vec{v}_i(t), \tag{2}
\end{gather}
```

```math
\begin{align}
\alpha \sum_{j \in n_c^i} \vec{v}_j(t) \\
\beta \sum_{j \in n_c^i} \vec{f}_{ij} \\
\gamma n_c \vec{\eta}_i
\end{align}
```

where $\Theta$ is a normalization operator $\Theta(\vec{y}) = \vec{y} / |\vec{y}|$ that serves to keep the speed fixed at $|\vec{v}| = v_0$, and $j \in n_c^i$ means that $j$ belongs to the $n_c$ interacting neighbors of $i$. The distance-dependent force $\vec{f}_ {ij}$ acts along the direction connecting $i$ and $j$; following [ref. 2](#ref), if $\vec{e}_ {ij}$ is the unit vector between $i$ and $j$, we take

```math
\begin{align}
\vec{f}_{ij} (r_{ij} < r_b) &= -\infty \vec{e}_{ij}, \tag{3} \\[1em]
\vec{f}_{ij} (r_b < r_{ij} < r_a) &= \frac{1}{4} \cdot \frac{r_{ij}-r_e}{r_a-r_e} \vec{e}_{ij}, \tag{4} \\[0.5em]
\vec{f}_{ij} (r_a < r_{ij} < r_0) &= \vec{e}_{ij}. \tag{5}
\end{align}
```

Finally, $\vec{\eta}_i$ is a random unit vector, independent for each bird and at each moment of time. The parameters $\alpha$, $\beta$, and $\gamma$ tune the strength of the alignment force, of the cohesion force, and of the noise, respectively.

Additionally, parameters are initialized according to [ref. 1](#ref), i.e., as listed in the following table:

<!---| $r_b$ | $r_e$ | $r_a$ | $r_0$ | $\alpha$ | $\beta$ | $\gamma$ | $n_c$ | $v_0$ |
| ----- | ----- | ----- | ----- | -------- | ------- | -------- | ----- | ----- |
| 0.2   | 0.5   | 0.8   | 0.1   | 35       | 5       | 1        | 8     | 0.05  |--->

| Parameter | Value  |
| :-------: | :----: |
| $r_b$     | $0.2$  |
| $r_e$     | $0.5$  |
| $r_a$     | $0.8$  |
| $r_0$     | $1$    |
| $\alpha$  | $35$   |
| $\beta$   | $5$    |
| $\gamma$  | $1$    |
| $n_c$     | $8$    |
| $v_0$     | $0.05$ |

The interaction range $n_c$ and the strength of the noise $\gamma$ can be changed as the simulation is running such that $n_c \in \[0, 32\]$ and $\gamma \in \[0, 2\]$.

## <a id="ref"/></a> References

1. Bialek W, et al. (2012). Statistical mechanics for natural flocks of birds. _Proc Natl Acad Sci USA_, 109, 4786–4791. doi: [10.1073/pnas.1118633109](https://doi.org/10.1073/pnas.1118633109)
   
2. Grégoire G, Chaté H. (2004). Onset of collective and cohesive motion. _Phys Rev Lett_, 92, 025702. doi: [10.1103/PhysRevLett.92.025702](https://doi.org/10.1103/PhysRevLett.92.025702)
