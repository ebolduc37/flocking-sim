# Flocking Simulation

Visualization of emergent collective behavior by simulating flocking on openFrameworks in C++ according to the self-propelled particles model described in ref. 1.

The following section is a selection of relevant excerpts adapted from the 2012 paper by Bialek et al.

## Statistical Mechanics for Natural Flocks of Birds

### Abstract

Flocking is a typical example of emergent collective behavior, where interactions between individuals produce collective patterns on the large scale. Here we show how a quantitative microscopic theory for directional ordering in a flock can be derived directly from field data. We construct the minimally structured (maximum entropy) model consistent with experimental correlations in large flocks of starlings. The maximum entropy model shows that local, pairwise interactions between birds are sufficient to correctly predict the propagation of order throughout entire flocks of starlings, with no free parameters. We also find that the number of interacting neighbors is independent of flock density, confirming that interactions are ruled by topological rather than metric distance. Finally, by comparing flocks of different sizes, the model correctly accounts for the observed scale invariance of long-range correlations among the fluctuations in flight direction.

(. . .)

### Results

\[...\]

#### Testing the Mechanistic Interpretation.

\[...\]

### Materials and Methods

\[...\]

#### Self-Propelled Particle Model.

We consider a model of self-propelled particles extensively studied in the literature \[2\]. Each particle moves with vector velocity $\vec{v}_i(t)$ according to the following equations:

```math
\begin{align}
\vec{v}_i(t+1) &= v_0 \Theta \left[ \alpha \sum_{j \in n_c^i} \vec{v}_j(t) + \beta \sum_{j \in n_c^i} \vec{f}_{ij} + n_c \vec{\eta}_i \right] \tag{1} \\[1em]
\vec{x}_i(t+1) &= \vec{x}_i(t) + \vec{v}_i(t), \tag{2}
\end{align}
```

where $\Theta$ is a normalization operator $\Theta(\vec{y}) = \vec{y} / |\vec{y}|$ that serves to keep the speed fixed at $|\vec{v}| = v_0$, and $j \in n_c^i$ means that $j$ belongs to the $n_c$ interacting neighbors of $i$. The distance-dependent force $\vec{f}_ {ij}$ acts along the direction connecting $i$ and $j$; following ref. 2, if $\vec{e}_ {ij}$ is the unit vector between $i$ and $j$, we take

```math
\begin{align}
\vec{f}_{ij} (r_{ij} < r_b) &= -\infty \vec{e}_{ij}, \tag{3} \\[1em]
\vec{f}_{ij} (r_b < r_{ij} < r_a) &= \frac{1}{4} \cdot \frac{r_{ij}-r_e}{r_a-r_e} \vec{e}_{ij}, \tag{4} \\[0.5em]
\vec{f}_{ij} (r_a < r_{ij} < r_0) &= \vec{e}_{ij}. \tag{5}
\end{align}
```

Finally, $\vec{\eta}_i$ is a random unit vector, independent for each bird and at each moment of time. The parameters $\alpha$ and $\beta$ tune the strength of the alignment and of the cohesion force, respectively; in particular, the strength of alignment is given by $J = v_0 \alpha ∕ n_c$.... Parameters were chosen as $r_0 = 1$ (to set the scale of distance), $r_b = 0.2$, $r_e = 0.5$, $r_a = 0.8$, $\alpha = 35$, $\beta = 5$, $v_0 = 0.05$....

## References

1. Bialek W, et al. (2012). Statistical mechanics for natural flocks of birds. _Proc Natl Acad Sci_, 109, 4786–4791. doi: [10.1073/pnas.1118633109](https://doi.org/10.1073/pnas.1118633109)

2. Grégoire G, Chaté H. (2004). Onset of collective and cohesive motion. _Phys Rev Lett_, 92, 025702. doi: [10.1103/PhysRevLett.92.025702](https://doi.org/10.1103/PhysRevLett.92.025702)
