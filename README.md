Add a particle with a doucle click.
Use the buttons under the scene to activate or desactivate random colors for the particles, and reducing the health points of the particles when there is a contact.
Modify the number of health points of the particles with the spinbox. It will  only affect the particles that will be created after this change (not the particles already on the sceen).
If the health points are activated, any contact with a red collider or with another particle will reduce the health points of a particle, while a contact with a green collider will increase them.
When the health points of a particle reach 0, the particle is destroyed and disappears from the screen.
The color of a particle indicates its health points.

For the implementation of the basic simulation, we used the equations of the assignement and followed the steps closely. We then modified our code to add several options and details to the simulation.

There are three different forms for the colliders: Plane, Sphere and Box.
The vertices of the box colliders were particularly hard to modelise but we managed to find a good equation for them.
We also managed to remove and destroy the particles after too many contacts using the std::remove_if method from the standard library.
We wanted to use inheritance for the colliders, but we had many difficulties to have a vector of colliders (that could be either Plane, Sphere or Box). We finally managed to keep this structure by using std:variant and std::visit, which works but seems to complexify the code.
At first the movements of the particles were instable as the particles kept vibrating, but we solved this problem by repeating several times the resolution of the physical system.
