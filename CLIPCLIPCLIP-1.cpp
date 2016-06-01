#include "clip.h"

#define max(a,b) ( (a>b) ? a : b )
#define min(a,b) ( (a<b) ? a : b )

#define max4(a,b,c,d) ( max(max(max(a,b),c),d) )
#define min4(a,b,c,d) ( min(min(min(a,b),c),d) )


namespace egc {

	// UNUL DINTRE SUBIECTE
	void ComputeClippingWindowNormals(std::vector<edge> &clipWindow) {

		for (int i = 0; i < clipWindow.size(); i++) {

			vec3 e = clipWindow.at(i).b - clipWindow.at(i).a;

			clipWindow.at(i).normal = vec3(e.y, -e.x, 0);
		}
	}


	bool isPointOutsideClippingWindow(const vec3 &p, const std::vector<edge> &clippingWindow) {
		
		for (int i = 0; i < clippingWindow.size(); i++) {
			vec3 v = p - clippingWindow.at(i).a;

			if (dotProduct(v, clippingWindow.at(i).normal) > 0)
				return true;
		}

		return false;
	}

	// presupun calculate normalele, altfel este varianta cu pantele m1 si m2 din celalalt proiect :)
	bool areTwoEdgesParallel(const edge &edgeToBeClipped, const edge &e) {
		return (dotProduct(edge.normal, edgeToBeClipped.b - edgeToBeClipped.a) == 0);
	}

	bool isPotentialEnteringPoint(const edge &e, const edge &edgeToBeClipped) {
		vec3 D = edgeToBeClipped.b - edgeToBeClipped.a;

		if (dotProduct(edge.normal, D) < 0)
			return true;
		else
			return false;
	}


	// CYRUS BECK fara functii create de noi
	int lineClip_CyrusBeck(std::vector<edge> clipWindow, vec3& p0, vec3& p1) {
		
		// calcul normale
		// se poate inlocui cu 		ComputeClippingWindowNormals(clipWindow);
		for (int i = 0; i < clipWindow.size(); i++) {

			vec3 e = clipWindow.at(i).b - clipWindow.at(i).a;

			clipWindow.at(i).normal = vec3(e.y, -e.x, 0);
		}

		// dreapta = un punct, iesim
		if (p1 == p0)
			return 0;
		/////////////

		float prodScalar, t;

		int tE = 0, tL = 1;
		vec3 D = p1 - p0;

		for (int i = 0; i < clipWindow.size(); i++) {
			prodScalar = dotProduct(clipWindow.at(i).normal, D);
			
			if (prodScalar != 0) {
				t = -dotProduct(clipWindow.at(i).normal, p0 - clipWindow.at(i).a) / prodScalar;

				if ((t>=0) && (t <= 1)) {
					if (prodScalar < 0)
						tE = max(t, tE);
					else
						tL = min(t, tL);
				}

			}
		}

		if (tE > tL)
			return -1;

		// MODIFICARE Versiunea 3
		vec3 p0final = p0 + D*tE;
		vec3 p1final = p0 + D*tL;

		p0 = p0final;
		p1 = p1final;

		return 1;
	}


	// ALT SUBIECT//

	void computeEdgeNormal(edge &e) {
		vec3 v = e.b - e.a;

		e.normal = vec3(v.y, -v.x, 0);
	}

	// aproape la fel ca si cea cu outside, dar cu true si false inversate
	bool isPointInsideClippingWindow(const vec3 &p, const std::vector<edge> &clippingWindow) {

		for (int i = 0; i < clippingWindow.size(); i++) {
			vec3 v = p - clippingWindow.at(i).a;

			if (dotProduct(v, clippingWindow.at(i).normal) > 0)
				return false;
		}

		return true;
	}


	float computeIntersectionPoint(const edge &lineToBeClipped, const edge e) {
		vec3 D = lineToBeClipped.b - lineToBeClipped.a;

		return -dotProduct(lineToBeClipped.a - e.a, e.normal) / dotProduct(D, e.normal);
	}


	void update_tE_or_tL(const float t, float &tE, float &tL, const edge e, const edge &lineToBeClipped) {
		vec3 D = lineToBeClipped.b - lineToBeClipped.a;
		float prodScalar = dotProduct(D, e.normal);

		if (prodScalar < 0)
			tE = max(tE, t);
		else
			tL = min(tL, t);
	}


	///////////// COHEN - SUTHERLAND

	const int INSIDE = 0;	// 0000
	const int LEFT = 1;		// 0001
	const int RIGHT = 2;	// 0010
	const int BOTTOM = 4;	// 0100
	const int TOP = 8;		// 1000


	// nu stiu care a fost antetul cerut la test... l-am modificat pe cel din clip.h (valoarea de return..
	// nu ma prind de ce ar fi un vector de intregi, poate sa reprezinte un vector de biti?)
	int computeCode(std::vector<vec3> clipWindow, const vec3 p) {

		// calculam minx, maxx, miny, maxy.. mi se pare cam ciudat ca facem de fiecare data, dar in functia din clip.h se 
		// transmitea clipWindow ca parametru.. poate e o greseala 

		// doar pt scriere mai usoara..
		int x[4];
		int y[4];

		for (int i = 0; i < 3; i++) {
			x[i] = clipWindow.at(i).x;
			y[i] = clipWindow.at(i).y;
		}
		//////////////////////////////


		int minX = min4(x[0], x[1], x[2], x[3]);
		int minY = min4(y[0], y[1], y[2], y[3]);
		int maxX = max4(x[0], x[1], x[2], x[3]);
		int maxY = max4(y[0], y[1], y[2], y[3]);

		//////////////////////////////


		int code = INSIDE;


		// da, trebuiau grupate 2 cate 2 cu else if, dar am zis sa nu pun else if ca sa nu incurc la test
		// si sa pun else if intre toate

		if (p.x < minX)
			code |= LEFT;

		if (p.x > maxX)
			code |= RIGHT;

		if (p.y < minY)
			code |= BOTTOM;

		if (p.y < maxY)
			code |= TOP;

		return code;
	}

	// din clip.h
	bool simpleRejection(std::vector<int> cod1, std::vector<int> cod2) {
		return (cod1 | cod2 == 0);
	}

	// din clip.h
	bool simpleAcceptance(std::vector<int> cod1, std::vector<int> cod2) {
		return (cod1 & cod2 != 0);
	}

	bool isInsideOrOutside(int cod) {
		// pff.. poate de asta ii complicata problema cu vectori de int :(
		return (cod == 0);
	}

	void invertPoint(vec3& p1, vec3& p2, int &cod1, int &cod2) {
		vec3 vectemp = p1;
		p1 = p2;
		p2 = vectemp;

		int codtemp = cod1;

		cod1 = cod 2;
		cod2 = codtemp;
	}

	// nu stiu antetul :) modific direct p1 aici.. poate ideea era alta :-?
	void computeIntersectPoint(vec3& p1, vece&p2, int opcode0) {
		int x0 = p1.x;
		int y0 = p1.y;
		int x1 = p2.x;
		int y1 = p2.y;

		if (opcode0 & TOP) {
			p1.x = x0 + (x1 - x0) * (maxY - y0) / (y1 - y0);
			p1.y = maxY;
		}
		else if (opcode0 & BOTTOM) {
			p1.x = x0 + (x1 - x0) * (minY - y0) / (y1 - y0);
			p1.y = minY;
		}
		else if (opcode0 & LEFT) {
			p1.x = minX;
			p1.y = y0 + (y1 - y0) * (minX - x0) / (x1-x0)
		}
		else if (opcode0 & RIGHT) {
			p1.x = maxX;
			p1.y = y0 + (y1 - y0) * (maxX - x0) / (x1 - x0);
		}
	}


	int lineClip_CohenSutherland(std::vector<vec3> clipWindow, vec3& p1, vec3& p2) {
		// iar trebuie min si max........ ceva-i ciudat

		int x[4];
		int y[4];

		for (int i = 0; i < 3; i++) {
			x[i] = clipWindow.at(i).x;
			y[i] = clipWindow.at(i).y;
		}
		//////////////////////////////


		int minX = min4(x[0], x[1], x[2], x[3]);
		int minY = min4(y[0], y[1], y[2], y[3]);
		int maxX = max4(x[0], x[1], x[2], x[3]);
		int maxY = max4(y[0], y[1], y[2], y[3]);
		//


		int opcode0 = computeCode(clipWindow, p1);
		int opcode1 = computeCode(clipWindow, p2);
		bool accept = false;

		while (true) {
			if (simpleAcceptance(opcode0, opcode1)) {
				accept = true;
				break;
			}
			else if (simpleRejection(opcode0, opcode1)) {
				break;
			}

			if (isInsideOrOutside(opcode0))
				invertPoint(p1, p2, opcode0, opcode1);

			computeIntersectionPoint(p1, p2, opcode0);

		}


	}


}