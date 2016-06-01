#include "clip.h"

#define min(a,b) ( (a<b) ? a :b)
#define max(a,b) ( (a>b) ? a: b)

#define min4(a,b,c,d) (min(min(min(a,b),c),d))
#define max4(a,b,c,d) (max(max(max(a,b),c),d))

namespace egc {
	typedef struct edge {
		vec3 a;
		vec3 b;
		vec3 normal;
	} edge;


	typedef struct edgeCS {
		vec3 vertex1;
		vec3 vertex2;
		std::vector<int> code1;
		std::vector<int> code2;
	} edgeCS;


	std::vector<int> computeCode(std::vector<edgeCS> clipWindow, const vec3 p) {
		std::vector<int> cod;

		// calculam xmin xmax ymin ymax
		// folosim x[4], y[4] ca sa scriem mai usor.. 
		// e destul (asa am facut si la test) sa luam primul capat al fiecarei muchii pt a parcurge toate varfurile
		float x[4], y[4];
		for (int i = 0; i < 4; i++) {
			x[i] = clipWindow.at(i).vertex1.x;
			y[i] = clipWindow.at(i).vertex2.y;
		}

		int xMin = min(x[0], x[1], x[2], x[3]);
		int xMax = max(x[0], x[1], x[2], x[3]);
		int yMin = min4(y[0], y[1], y[2], y[3]);
		int yMax = max4(y[0], y[1], y[2], y[3]);
		/////////////////////////////////


		if (p.y > yMax)
			cod.push_back(1);
		else
			cod.push_back(0);

		if (p.y < yMin)
			cod.push_back(1);
		else
			cod.push_back(0);

		if (p.x > xMax)
			cod.push_back(1);
		else
			cod.push_back(0);

		if (p.x < xMin)
			cod.push_back(1);
		else
			cod.push_back(0);

		return cod;
	}

	/*	bool simpleRejection(std::vector<int> cod1, std::vector<int> cod2) {
			for (int i = 0; i < cod1.size(); i++)
				if ((cod1.at(i) == 1) && (cod2.at(i) == 1))
					return true;

			return false;
		}

		bool simpleAcceptance(std::vector<int> cod1, std::vector<int> cod2) {
			for (int i = 0; i < cod1.size(); i++)
				if ((cod1.at(i) == 1) || (cod2.at(i) == 1))
					return false;

			return true;
		}*/

		/*	bool isInsideOrOutside(std::vector<int> cod) {
				for (int i = 0; i < cod.size(); i++)
					if (cod.at(i) == 1)
						return false;

				return true;
			} */



			/*
				Mie la test imi cerea ca functia sa returneze 0 pt simple acceptance, 1 pt simple rejectance, -2 daca nu e niciuna din astea
			*/
	int isLineInsideOrOutside(edgeCS &edgeToBeclipped) {
		bool accept = true;
		bool reject = false;

		std::vector<int> cod1, cod2;

		for (int i = 0; i < cod1.size(); i++) {
			// cond pe respingere simpla e ca SI pe biti intre cele 2 coduri
			// sa fie != 0 ; daca gasim o pozitie unde bitii sunt ambii 1 (SI intre ei = 1), daca am face SI pe biti
			// am obtine ceva != 0, deci putem spune reject = true
			if (cod1.at(i) && cod2.at(i))
				reject = true;

			// cond de acceptare simpla e ca SAU pe biti intre coduri sa fie 0
			// daca gasim o pozitie unde cel putin 1 bit e 1, SAU intre ei o sa fie 1 
			// => nu putem avea rezultat nul
			if (cod1.at(i) || cod2.at(i))
				accept = false;
		}

		if (accept & !reject)
			return 0;
		if (!accept & reject);
		return 1;

		return -2;
	}


	/*
		Se face intersectia. primul capat al muchiei e cel care se poate modifica (se preciza in header)
	*/
	void computeIntersectionPoint(edgeCS &edgeToBeClipped, int xmin, int xmax, int ymin, int ymax) {
		std::vector<int> cod = edgeToBeClipped.code1;
		float x1 = edgeToBeClipped.vertex1.x;
		float y1 = edgeToBeClipped.vertex1.y;
		float x2 = edgeToBeClipped.vertex2.x;
		float y2 = edgeToBeClipped.vertex2.y;


		if (cod.at(0) && (y1 != y2)) {
			edgeToBeClipped.vertex1.y = ymax;
			edgeToBeClipped.vertex1.x = x1 + (x2 - x1)* (ymax - y1) / (y2 - y1);
		}
		else if (cod.at(1) && (y1 != y2)) {
			edgeToBeClipped.vertex1.y = ymin;
			edgeToBeClipped.vertex1.x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
		}
		else if (cod.at(2) && (x1 != x2)) {
			edgeToBeClipped.vertex1.x = xmax;
			edgeToBeClipped.vertex1.y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
		}
		else if (cod.at(3) && (x1 != x2)) {
			edgeToBeClipped.vertex1.x = xmin;
			edgeToBeClipped.vertex1.y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
		}
	}


	void invertPoints(edgeCS &e) {
		vec3 vectemp;
		vectemp = e.vertex1;
		e.vertex1 = e.vertex2;
		e.vertex2 = vectemp;

		std::vector<int> vec;
		vec = e.code1;
		e.code1 = e.code2;
		e.code2 = vec;
	}


	// eu ceva de genul am avut la test si mi-am implementat functia de mai sus [o aveam deja neimplementata.. probabil poate pica aceea la unele subiecte
	// (are acelasi nume, dar cea de dinauntru
	// apelata e de fapt cea de mai sus)
	void computeCode(std::vector<edgeCS> clipWindow, edgeCS &edgeToBeClipped) {
		edgeToBeClipped.code1 = computeCode(clipWindow, edgeToBeClipped.vertex1);
		edgeToBeClipped.code2 = computeCode(clipWindow, edgeToBeClipped.vertex2);
	}


	// /!\ ATENTIE LA VALORILE DE RETURN PT FUNCTIILE CU ALGORITMII.. EU AM OBSERVAT CA LE IA IN CONSIDERARE
	// de ex, daca puneam return 1 (mai jos) si la simple rejectance nu puncta
	int lineClip_CohenSutherland(std::vector<edgeCS> clipWindow, edgeCS edgeToBeClipped) {
		std::vector<int> cod1, cod2;

		// calculam xmin xmax ymin ymax

		// folosim x[4], y[4] ca sa scriem mai usor.. 
		// e destul (asa am facut si la test) sa luam primul capat al fiecarei muchii pt a parcurge toate varfurile
		float x[4], y[4];
		for (int i = 0; i < 4; i++) {
			x[i] = clipWindow.at(i).vertex1.x;
			y[i] = clipWindow.at(i).vertex2.y;
		}

		int xMin = min4(x[0], x[1], x[2], x[3]);
		int xMax = max4(x[0], x[1], x[2], x[3]);
		int yMin = min4(y[0], y[1], y[2], y[3]);
		int yMax = max4(y[0], y[1], y[2], y[3]);
		/////////////////////////////////



		while (true) {
			computeCode(clipWindow, edgeToBeClipped);

			cod1 = edgeToBeClipped.code1;
			cod2 = edgeToBeClipped.code2;

			int decizie = isLineInsideOrOutside(edgeToBeClipped);
			if (decizie == 0) {
				// simple acceptance
				return 1;
			}
			else if (decizie == 1) {
				// simpla respingere
				return -1;
			}

			// verificamd daca primul varf e in interior (code == 0)
			// daca gasim un "bit" (int) din cod !=0, atunci codul e dif de 0 => nu e in interior
			// daca e 0 , schimbam capetele muchiei intre ele (si codurile) cu fct de mai sus
			bool inside = true;
			for (int i = 0; i < cod1.size(); i++)
				if (cod1.at(i)) {
					inside = false;
					break;
				}
			if (inside)
				invertPoints(edgeToBeClipped);

			computeIntersectionPoint(edgeToBeClipped, xMin, xMax, yMin, yMax);
		}

		return 1;
	}
}
