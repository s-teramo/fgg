fgg
===

Flip Graph Generator for a Convex Polygon

Description
---
fgg is for generating flip graphs of convex n-gons.
The following image is a flip graph of the regular heptagon.
Each vertex is drawn with a triangulation of the heptagon.
Vertices are connected by an edge (blue line),
if they are transformed from a flip operation.
![heptagon](heptagon-image.jpg)
We have confirmed that fgg generates flip graphs correctly up to 15-gon.


Required Library
---
Since fgg uses
[igraph library](http://igraph.sourceforge.net/ "igraph library"),
user has to install it. 
However, we consider other graph library, too.
We may exchange graph library at some future dates,
because igraph library is not so fast for creating a large graph
structure.


Install
---
	cmake .
	make
	make install


