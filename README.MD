COMP 371 PROJECT <br/>
AUTHOR: CHRISTIAN PLOURDE <br/>
STUDENT ID: 26572499 <br/>
------------------------------------------------------------------------------------------------------------------

Upon opening the application, there is CLI that allows the user to specify where the scene file to be rendered is
located as well as if the user wishes to save the image to file upon render. If this option is selected, the user will
be prompted for a location to save the file. The last choice the user must make before rendering is whether or not
the scene should be rendered with shadows. If the user selects no for this, the shadow ray casting portion of the ray
tracing for each object will be ignored.

Next, the scene file is loaded into appropriate objects. These objects (sphere, plane, mesh...) all derive from a
base class called scene object. This allows us to quickly cycle through the objects since that can be pointed to
by a scene object pointer. This is particularly useful when casting shadow rays since the intersection must be computed
for all other objects in the scene.

A depth buffer object was also created in order to simulate what is done in OpenGL. The depth buffer is a linked list
the size of the number of pixels and contains a pointer that is shifted every time giving an access time of O(1). When
we render an object, we look at the depth for the pixel we are currently on and compare it to the depth in the buffer.
If the depth of the pixel we are on is closer than what is in the depth buffer, we update the depth buffer, compute the
lighting, color the pixel appropriately, compute shadows, etc. and then shift the pointer to the next pixel. If the depth
is greater than what is in the buffer for that pixel, then that pixel should not be colored. We then shift the pointer and
skip the rest of the iteration. This allows us to draw objects in any order and the result is the same no matter then order.

When rendering an object, the same ray is used and moved for every iteration (pixel). This allows us to reuse the same
object every time instead of using many rays. Next, we compute the intersection based on the appropriate method. For the
spheres, we are computing the sphere intersection which is essentially solving a quadratic equation. For each of these
a bias was added of 1e-6 to account for floating point errors. For the plane, we solve the plane equation, again using a
bias.

For the mesh, things are more complicated. Because I created my own Vector and Matrix objects, I had to rewrite the
object loader functions that we were using for OpenGL. I trimmed down the unnecessary bits as well. It only reads in
information about the vertices, normals, and face construction lines (only the info for the vertices (v1// v2// v3//)).
Once this information has been read, a MeshFace object is created, which contains the three vertices of the triangle and
its normal (which is computed by taking the cross product of the vectors connecting the vertices when they are set).

This means that the Mesh object is basically just a collection of mesh faces, and when we render it, we should render
each of its mesh faces independently. The mesh intersection is computed by calculating if (for each mesh face) if the
ray intersects with the plane that holds the triangle. Once we have confirmed that it intersects, we must determine if
the point of intersection is inside the triangle. This is done by applying the inside out test. Once we know if there is
an intersection we can draw it if it is in front of whatever is in the depth buffer.

Whenever an object is rendered, we cast a shadow ray from the point of intersection to each light in the scene. If that
shadow ray intersects with any other object in the scene, then the pixel we are currently rendering should be in shadow
and whatever color was initially computed is halved so it appears darker. This effect can stack if multiple objects
occlude that pixel (shadows cast from other objects or other lights) to produce even darker shadows.

Another check that is done (this was important for the second mesh scene in particular) is when we check the depth
buffer, we also check if the intersection point is on the camera (actually within a bias) and if it is, we don't draw
that. If we don't do this, the whole scene is intersected and all we see is black since the first intersection is right
where the camera is so it can't see anything behind that point.