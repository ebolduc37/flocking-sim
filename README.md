# Flocking Simulation

This application allows for the visualization of emergent collective behavior by simulating a flock of boids on openFrameworks in C++ according to a modified version of the self-propelled particles model described in [ref. 1](#ref).

## openFrameworks Simulation

## Commands

| Key                                                         | Effect                              |
| :-:                                                         | -                                   |
| <code>P</code>                                              | Change the look of the simulation   |
| <code>R</code>                                              | Randomize the position of all boids |
| <code>W</code>/<code>A</code>/<code>S</code>/<code>D</code> | Rotate the cube                     |
| <code>Q</code>/<code>E</code>                               | Zoom in/out of the space            |
| <code>SPACEBAR</code>                                       | Play/pause the simulation           |
| <code>UP</code>/<code>DOWN</code>                           | Tune the strength of the noise      |
| <code>LEFT</code>/<code>RIGHT</code>                        | Tune the interaction range          |
| <code>ESC</code>                                            | Exit the simulation                 |

## Self-Propelled Particle Model

I considered the self-propelled particles model described in [ref. 1](#ref) and introduced a parameter modulating the strength of the noise. Each particle moves with vector velocity $\vec{v}_i(t)$ according to the following equations:

<a id="eqs"/></a>
```math
\begin{align}
\vec{v}_i(t+1) &= v_0 \Theta \left[ \alpha \sum_{j \in n_c^i} \vec{v}_j(t) + \beta \sum_{j \in n_c^i} \vec{f}_{ij} + \gamma n_c \vec{\eta}_i \right] \tag{1} \\[1em]
\vec{x}_i(t+1) &= \vec{x}_i(t) + \vec{v}_i(t), \tag{2}
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

Additionally, parameters are initialized according to [ref. 1](#ref), i.e.,

| $n_c$ | $r_b$ | $r_e$ | $r_a$ | $r_0$ | $\alpha$ | $\beta$ | $v_0$ |
| ----  | ----- | ----- | ----- | ----- | -------- | ------- | ----- |
| 8     | 0.2   | 0.5   | 0.8   | 0.1   | 35       | 5       | 0.05  |

The interaction range $n_c$ and the strength of the noise $\gamma$ can be modified as the simulation is running such that $n_c \in \[0, 32\]$ and $\gamma \in \[0, 2\]$.

## <a id="ref"/></a> References

1. Bialek W, et al. (2012). Statistical mechanics for natural flocks of birds. _Proc Natl Acad Sci USA_, 109, 4786–4791. doi: [10.1073/pnas.1118633109](https://doi.org/10.1073/pnas.1118633109)
   
2. Grégoire G, Chaté H. (2004). Onset of collective and cohesive motion. _Phys Rev Lett_, 92, 025702. doi: [10.1103/PhysRevLett.92.025702](https://doi.org/10.1103/PhysRevLett.92.025702)
