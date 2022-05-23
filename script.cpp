#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <thread>
#include <chrono>

#include "window.hpp"
#include "renderer.hpp"
#include "graphics.hpp"
#include "graphics3d.hpp"
#include "transform.hpp"
#include "mdl/parser.hpp"
#include "mdl/symtab.hpp"
#include "mdl/y.tab.hpp"

// int lastop;
// struct command op[MAX_COMMANDS];

void parse(Window &w, Renderer &r, std::string fileName)
{
	std::ifstream file(fileName);

	Graphics g;
	Graphics3D g3d;
	Transform t;

	int color[] = {255, 255, 255};

	while (file.good())
	{
		std::string cmd;
		file >> cmd;

		g.clear();
		g3d.clear();
		t.reset();

		if (cmd == "line")
		{
			int coords[6];
			file >> coords[0] >> coords[1] >> coords[2] >> coords[3] >> coords[4] >> coords[5];

			g.addEdge(coords[0], coords[1], coords[2], coords[3], coords[4], coords[5]);
		}
		else if (cmd == "circle")
		{
			int coords[3];
			int radius;

			file >> coords[0] >> coords[1] >> coords[2] >> radius;
			g.addCircle(coords[0], coords[1], coords[2], radius);
		}
		else if (cmd == "bezier")
		{
			int coords[8];

			file >> coords[0] >> coords[1] >> coords[2] >> coords[3] >> coords[4] >> coords[5] >> coords[6] >> coords[7];
			g.addBezierCurve(coords[0], coords[1], 0, coords[2], coords[3], 0,
							 coords[4], coords[5], 0, coords[6], coords[7], 0);
		}
		else if (cmd == "hermite")
		{
			int coords[4];
			int rates[4];

			file >> coords[0] >> coords[1] >> coords[2] >> coords[3] >> rates[0] >> rates[1] >> rates[2] >> rates[3];
			g.addHermiteCurve(coords[0], coords[1], 0, rates[0], rates[1], 0,
							  coords[2], coords[3], 0, rates[2], rates[3], 0);
		}
		else if (cmd == "box")
		{
			int coords[3];
			int dimensions[3];

			file >> coords[0] >> coords[1] >> coords[2] >> dimensions[0] >> dimensions[1] >> dimensions[2];
			g3d.addBox(coords[0], coords[1], coords[2], dimensions[0], dimensions[1], dimensions[2]);
		}
		else if (cmd == "sphere")
		{
			int coords[3];
			int radius;

			file >> coords[0] >> coords[1] >> coords[2] >> radius;
			g3d.addSphere(coords[0], coords[1], coords[2], radius, 300, 300);
		}
		else if (cmd == "torus")
		{
			int coords[3];
			int radii[2];

			file >> coords[0] >> coords[1] >> coords[2] >> radii[0] >> radii[1];
			g3d.addTorus(coords[0], coords[1], coords[2], radii[0], radii[1], 300, 300);
		}
		else if (cmd == "ident")
		{
			t.reset();
		}
		else if (cmd == "scale")
		{
			double factor[3];
			file >> factor[0] >> factor[1] >> factor[2];

			t.addDilation(factor[0], factor[1], factor[2]);
		}
		else if (cmd == "move")
		{
			int amt[3];
			file >> amt[0] >> amt[1] >> amt[2];

			t.addTranslation(amt[0], amt[1], amt[2]);
		}
		else if (cmd == "rotate")
		{
			char axis;
			double theta;
			file >> axis >> theta;

			switch (axis)
			{
			case 'x':
				t.addRotation(theta, Axis::X);
				break;
			case 'y':
				t.addRotation(theta, Axis::Y);
				break;
			case 'z':
				t.addRotation(theta, Axis::Z);
				break;
			}
		}
		else if (cmd == "apply")
		{
			g.transform(t);
			g3d.transform(t);
		}
		else if (cmd == "pop")
		{
			r.deletePlane();
		}
		else if (cmd == "push")
		{
			r.addPlane();
		}
		else if (cmd == "display")
		{
			r.setColor(color[0], color[1], color[2]);

			w.draw("temp.ppm", false);
			w.display();

			// std::cin.ignore();
			system("rm temp.ppm");
		}
		else if (cmd == "save")
		{
			r.setColor(color[0], color[1], color[2]);

			std::string outputFile;
			file >> outputFile;

			w.draw(outputFile, false);
		}
		else if (cmd == "color")
		{
			file >> color[0] >> color[1] >> color[2];
		}
		else if (cmd == "clear")
		{
			r.setColor(0, 0, 0);
			r.fill();
			r.clearZBuffer();
		}
		else if (cmd == "fill")
		{
			int fillColor[] = {0, 0, 0};
			file >> fillColor[0] >> fillColor[1] >> fillColor[2];

			r.setColor(fillColor[0], fillColor[1], fillColor[2]);
			r.fill();
		}
		else if (cmd.find("#") != std::string::npos)
		{
			std::string skip;
			getline(file, skip);
		}
		else if (cmd != "")
		{
			std::cout << "bad command given {" << cmd << "}\n";
		}

		r.transformPlane(t);

		r.setColor(color[0], color[1], color[2]);
		r.draw(g);
		r.draw(g3d);
	}
}

void print_pcode()
{
	print_symtab();
	int i;
	for (i = 0; i < lastop; i++)
	{
		printf("%d: ", i);
		switch (op[i].opcode)
		{
		case LIGHT:
			printf("Light: %s at: %6.2f %6.2f %6.2f",
				   op[i].op.light.p->name,
				   op[i].op.light.c[0], op[i].op.light.c[1],
				   op[i].op.light.c[2]);
			break;
		case AMBIENT:
			printf("Ambient: %6.2f %6.2f %6.2f",
				   op[i].op.ambient.c[0],
				   op[i].op.ambient.c[1],
				   op[i].op.ambient.c[2]);
			break;

		case CONSTANTS:
			printf("Constants: %s", op[i].op.constants.p->name);
			break;
		case SAVE_COORDS:
			printf("Save Coords: %s", op[i].op.save_coordinate_system.p->name);
			break;
		case CAMERA:
			printf("Camera: eye: %6.2f %6.2f %6.2f\taim: %6.2f %6.2f %6.2f",
				   op[i].op.camera.eye[0], op[i].op.camera.eye[1],
				   op[i].op.camera.eye[2],
				   op[i].op.camera.aim[0], op[i].op.camera.aim[1],
				   op[i].op.camera.aim[2]);

			break;
		case SPHERE:
			printf("Sphere: %6.2f %6.2f %6.2f r=%6.2f",
				   op[i].op.sphere.d[0], op[i].op.sphere.d[1],
				   op[i].op.sphere.d[2],
				   op[i].op.sphere.r);
			if (op[i].op.sphere.constants != NULL)
			{
				printf("\tconstants: %s", op[i].op.sphere.constants->name);
			}
			if (op[i].op.sphere.cs != NULL)
			{
				printf("\tcs: %s", op[i].op.sphere.cs->name);
			}

			break;
		case TORUS:
			printf("Torus: %6.2f %6.2f %6.2f r0=%6.2f r1=%6.2f",
				   op[i].op.torus.d[0], op[i].op.torus.d[1],
				   op[i].op.torus.d[2],
				   op[i].op.torus.r0, op[i].op.torus.r1);
			if (op[i].op.torus.constants != NULL)
			{
				printf("\tconstants: %s", op[i].op.torus.constants->name);
			}
			if (op[i].op.torus.cs != NULL)
			{
				printf("\tcs: %s", op[i].op.torus.cs->name);
			}

			break;
		case BOX:
			printf("Box: d0: %6.2f %6.2f %6.2f d1: %6.2f %6.2f %6.2f",
				   op[i].op.box.d0[0], op[i].op.box.d0[1],
				   op[i].op.box.d0[2],
				   op[i].op.box.d1[0], op[i].op.box.d1[1],
				   op[i].op.box.d1[2]);
			if (op[i].op.box.constants != NULL)
			{
				printf("\tconstants: %s", op[i].op.box.constants->name);
			}
			if (op[i].op.box.cs != NULL)
			{
				printf("\tcs: %s", op[i].op.box.cs->name);
			}

			break;
		case LINE:
			printf("Line: from: %6.2f %6.2f %6.2f to: %6.2f %6.2f %6.2f",
				   op[i].op.line.p0[0], op[i].op.line.p0[1],
				   op[i].op.line.p0[1],
				   op[i].op.line.p1[0], op[i].op.line.p1[1],
				   op[i].op.line.p1[1]);
			if (op[i].op.line.constants != NULL)
			{
				printf("\n\tConstants: %s", op[i].op.line.constants->name);
			}
			if (op[i].op.line.cs0 != NULL)
			{
				printf("\n\tCS0: %s", op[i].op.line.cs0->name);
			}
			if (op[i].op.line.cs1 != NULL)
			{
				printf("\n\tCS1: %s", op[i].op.line.cs1->name);
			}
			break;
		case MESH:
			printf("Mesh: filename: %s", op[i].op.mesh.name);
			if (op[i].op.mesh.constants != NULL)
			{
				printf("\tconstants: %s", op[i].op.mesh.constants->name);
			}
			break;
		case SET:
			printf("Set: %s %6.2f",
				   op[i].op.set.p->name,
				   op[i].op.set.p->s.value);
			break;
		case MOVE:
			printf("Move: %6.2f %6.2f %6.2f",
				   op[i].op.move.d[0], op[i].op.move.d[1],
				   op[i].op.move.d[2]);
			if (op[i].op.move.p != NULL)
			{
				printf("\tknob: %s", op[i].op.move.p->name);
			}
			break;
		case SCALE:
			printf("Scale: %6.2f %6.2f %6.2f",
				   op[i].op.scale.d[0], op[i].op.scale.d[1],
				   op[i].op.scale.d[2]);
			if (op[i].op.scale.p != NULL)
			{
				printf("\tknob: %s", op[i].op.scale.p->name);
			}
			break;
		case ROTATE:
			printf("Rotate: axis: %6.2f degrees: %6.2f",
				   op[i].op.rotate.axis,
				   op[i].op.rotate.degrees);
			if (op[i].op.rotate.p != NULL)
			{
				printf("\tknob: %s", op[i].op.rotate.p->name);
			}
			break;
		case BASENAME:
			printf("Basename: %s", op[i].op.basename.p->name);
			break;
		case SAVE_KNOBS:
			printf("Save knobs: %s", op[i].op.save_knobs.p->name);
			break;
		case TWEEN:
			printf("Tween: %4.0f %4.0f, %s %s",
				   op[i].op.tween.start_frame,
				   op[i].op.tween.end_frame,
				   op[i].op.tween.knob_list0->name,
				   op[i].op.tween.knob_list1->name);
			break;
		case FRAMES:
			printf("Num frames: %4.0f", op[i].op.frames.num_frames);
			break;
		case VARY:
			printf("Vary: %4.0f %4.0f, %4.0f %4.0f",
				   op[i].op.vary.start_frame,
				   op[i].op.vary.end_frame,
				   op[i].op.vary.start_val,
				   op[i].op.vary.end_val);
			break;
		case PUSH:
			printf("Push");
			break;
		case POP:
			printf("Pop");
			break;
		case GENERATE_RAYFILES:
			printf("Generate Ray Files");
			break;
		case SAVE:
			printf("Save: %s", op[i].op.save.p->name);
			break;
		case SHADING:
			printf("Shading: %s", op[i].op.shading.p->name);
			break;
		case SETKNOBS:
			printf("Setknobs: %f", op[i].op.setknobs.value);
			break;
		case FOCAL:
			printf("Focal: %f", op[i].op.focal.value);
			break;
		case DISPLAY:
			printf("Display");
			break;
		}
		printf("\n");
	}
}

void parse_mdl()
{
	Window w(500, 500);
	Renderer r(w);

	w.invertY();

	// settings for test
	r.setColor(255, 255, 255);
	r.setAmbientLight();
	r.addPointLight(.5, .75, 1);

	//settings for gallery
	// r.setColor(255, 255, 255);
	// r.setAmbientLight();

	// r.setColor(255, 10, 10);
	// r.addPointLight(0, 1, 0);

	// r.setColor(255, 255, 255);
	// r.addPointLight(0, -1, 0);

	Graphics g;
	Graphics3D g3d;
	Transform t;

	for (int i = 0; i < lastop; i++)
	{
		std::string cppString;

		g.clear();
		g3d.clear();
		t.reset();

		switch (op[i].opcode)
		{
		case LIGHT:
			break;
		case AMBIENT:
			break;
		case CONSTANTS:
			break;
		case SAVE_COORDS:
			break;
		case CAMERA:
			break;
		case SPHERE:
			if (op[i].op.sphere.constants != NULL)
			{
				SYMTAB *t = lookup_symbol(op[i].op.sphere.constants->name);

				g3d.setAmbient(t->s.c->r[0], t->s.c->g[0], t->s.c->b[0]);
				g3d.setDiffuse(t->s.c->r[1], t->s.c->g[1], t->s.c->b[1]);
				g3d.setSpecular(t->s.c->r[2], t->s.c->g[2], t->s.c->b[2]);
			}

			g3d.addSphere(
				op[i].op.sphere.d[0],
				op[i].op.sphere.d[1],
				op[i].op.sphere.d[2],
				op[i].op.sphere.r,
				300, 300);
			break;
		case TORUS:
			if (op[i].op.torus.constants != NULL)
			{
				SYMTAB *t = lookup_symbol(op[i].op.box.constants->name);

				g3d.setAmbient(t->s.c->r[0], t->s.c->g[0], t->s.c->b[0]);
				g3d.setDiffuse(t->s.c->r[1], t->s.c->g[1], t->s.c->b[1]);
				g3d.setSpecular(t->s.c->r[2], t->s.c->g[2], t->s.c->b[2]);
			}

			g3d.addTorus(op[i].op.torus.d[0],
						 op[i].op.torus.d[1],
						 op[i].op.torus.d[2],
						 op[i].op.torus.r0,
						 op[i].op.torus.r1,
						 300, 300);
			break;
		case BOX:
			if (op[i].op.sphere.constants != NULL)
			{
				SYMTAB *t = lookup_symbol(op[i].op.box.constants->name);

				g3d.setAmbient(t->s.c->r[0], t->s.c->g[0], t->s.c->b[0]);
				g3d.setDiffuse(t->s.c->r[1], t->s.c->g[1], t->s.c->b[1]);
				g3d.setSpecular(t->s.c->r[2], t->s.c->g[2], t->s.c->b[2]);
			}

			g3d.addBox(op[i].op.box.d0[0],
					   op[i].op.box.d0[1],
					   op[i].op.box.d0[2],
					   op[i].op.box.d1[0],
					   op[i].op.box.d1[1],
					   op[i].op.box.d1[2]);
			break;
		case LINE:
			g.addEdge(op[i].op.line.p0[0],
					  op[i].op.line.p0[1],
					  op[i].op.line.p0[2],
					  op[i].op.line.p1[0],
					  op[i].op.line.p1[1],
					  op[i].op.line.p1[2]);
			break;
		case MESH:
			break;
		case SET:
			break;
		case MOVE:
			t.addTranslation(op[i].op.move.d[0],
							 op[i].op.move.d[1],
							 op[i].op.move.d[2]);
			break;
		case SCALE:
			t.addDilation(op[i].op.scale.d[0],
						  op[i].op.scale.d[1],
						  op[i].op.scale.d[2]);

			break;
		case ROTATE:
			if (op[i].op.rotate.axis == 0)
			{
				t.addRotation(op[i].op.rotate.degrees, Axis::X);
				break;
			}
			else if (op[i].op.rotate.axis == 1)
			{
				t.addRotation(op[i].op.rotate.degrees, Axis::Y);
				break;
			}
			else if (op[i].op.rotate.axis == 2)
			{
				t.addRotation(op[i].op.rotate.degrees, Axis::Z);
				break;
			}
			break;
		case BASENAME:
			break;
		case SAVE_KNOBS:
			break;
		case TWEEN:
			break;
		case FRAMES:
			break;
		case VARY:
			break;
		case PUSH:
			r.addPlane();
			break;
		case POP:
			r.deletePlane();
			break;
		case GENERATE_RAYFILES:
			break;
		case SAVE:
			cppString = op[i].op.save.p->name;

			w.draw(cppString, false);
			break;
		case SHADING:
			break;
		case SETKNOBS:
			break;
		case FOCAL:
			break;
		case DISPLAY:
			w.draw("temp.ppm", false);
			w.display();

			// std::cin.ignore();
			system("rm temp.ppm");
		}

		r.transformPlane(t);

		r.draw(g);
		r.draw(g3d);
	}
}