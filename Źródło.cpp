#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>

using namespace std;

typedef struct alfabet
{
	int* litery;

};

typedef struct wirnik
{
	alfabet alf;
	int* notches;
	int notch_number;

};

typedef struct reflektor
{
	alfabet alf;
};

void zainicjuj_wirniki(wirnik* wirniki, int n, int m)
{	
	int no;		
	for (int i = 0; i < m; i++)
	{
		wirniki[i].alf.litery = (int*)malloc(sizeof(int) * n);
	}
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%d", &wirniki[i].alf.litery[j]);
		}
		scanf("%d", &no);

		wirniki[i].notches = (int*)malloc(sizeof(int) * no);
		wirniki[i].notch_number = no;

		for (int k = 0; k < no; k++)
		{
			scanf("%d", &wirniki[i].notches[k]);
		}
	}
	
}

void zainicjuj_reflektory(reflektor* reflektory, int n, int l)
{
	for (int i = 0; i < l; i++)
	{
		reflektory[i].alf.litery = (int*)malloc(sizeof(int) * n);
	}

	for (int i = 0; i < l; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%d", &reflektory[i].alf.litery[j]);
		}
	}
}

void wybor_wirnikow(wirnik *maszyna_wir, wirnik *wirnik_o, int *start, int n, int k, wirnik *wirniki)
{
	int index_W;
	
	for (int i = 0; i < k; i++)
	{
		scanf("%d", &index_W);
		scanf("%d", &start[i]);

		maszyna_wir[i].alf.litery = (int*)malloc(sizeof(int) * (n + 1));
		wirnik_o[i].alf.litery = (int*)malloc(sizeof(int) * (n + 1));
		maszyna_wir[i].alf.litery[0] = 0;
		wirnik_o[i].alf.litery[0] = 0;

		for (int j = 1; j <= n; j++)
		{
			int x = wirniki[index_W].alf.litery[j - 1];
			maszyna_wir[i].alf.litery[j] = x;
			wirnik_o[i].alf.litery[x] = j;
		}
		maszyna_wir[i].notches = wirniki[index_W].notches;
		maszyna_wir[i].notch_number = wirniki[index_W].notch_number;
	}
}

void wybor_reflektora(reflektor maszyna_ref, reflektor *reflektory, int n, int r)
{
	maszyna_ref.alf.litery[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		maszyna_ref.alf.litery[i] = reflektory[r].alf.litery[i - 1];
	}
}



void zwolnij_po_zadaniu(wirnik *maszyna_wir, wirnik *wir_reverse, reflektor maszyna_ref, int *start, int *obroty, int k)
{
	for (int i = 0; i < k; i++)
	{
		free(maszyna_wir[i].alf.litery);
		free(wir_reverse[i].alf.litery);
	}

	free(maszyna_ref.alf.litery);
	free(start);
	free(maszyna_wir);
	free(wir_reverse);
	free(obroty);
}



void zwolnij_na_koniec(wirnik* wirniki, reflektor* reflektory, int l, int m)
{
	for (int i = 0; i < l; i++)
	{
		free(reflektory[i].alf.litery);
	}

	for (int i = 0; i < m; i++)
	{
		free(wirniki[i].alf.litery);
		free(wirniki[i].notches);
	}

	free(wirniki);
	free(reflektory);
}


int main()
{
	int n, m, l;
	scanf("%d %d", &n, &m);

	wirnik* wirniki;
	reflektor* reflektory;

	wirniki = (wirnik*)malloc(sizeof(wirnik) * n);
	zainicjuj_wirniki(wirniki, n, m);

	scanf("%d", &l);
	reflektory = (reflektor*)malloc(sizeof(reflektor) * l);

	zainicjuj_reflektory(reflektory, n, l);
	
	int p, k, *start, r, letter;

	wirnik* maszyna_wir, *wirnik_o;
	reflektor maszyna_ref;

	scanf("%d", &p);

	for (int a = 0; a < p; a++)
	{
		scanf("%d", &k);
		maszyna_wir = (wirnik*)malloc(sizeof(wirnik) * k);
		wirnik_o = (wirnik*)malloc(sizeof(wirnik) * k);
		start = (int*)malloc(sizeof(int) * k);
		maszyna_ref.alf.litery = (int*)malloc(sizeof(int) * (n + 1));
		
		wybor_wirnikow(maszyna_wir, wirnik_o, start, n, k, wirniki);

		scanf("%d", &r);
		wybor_reflektora(maszyna_ref, reflektory, n,r);
		
		int* obroty = (int*)malloc(sizeof(int) * k);
		for (int i = 0; i < k; i++)
		{
			obroty[i] = 0;
		}
		
			
		scanf("%d", &letter);

		bool double_step = false;

		while (letter != 0)
		{
			int  x = 0;
			bool has_moved[3] = { false,false,false };

			obroty[0]++; has_moved[0] = true;

			int no_notches = maszyna_wir[0].notch_number, no_notches1 = maszyna_wir[1].notch_number, no_notches2 = maszyna_wir[2].notch_number;

			if (k > 1)
			{
				bool has_notched0 = false;

				if (double_step == true)
				{
					obroty[1]++;
					has_moved[1] = true;
					obroty[2]++;
					has_moved[2] = true;
					double_step = false;
				}

				int index = ((start[0] + obroty[0] - 1) % n) + 1;
				for (int i = 0; i < no_notches; i++)
				{
					if ((index == maszyna_wir[0].notches[i]) && (obroty[0] > 1))
					{
						has_notched0 = true; break;
					}
				}
				if (has_notched0 == true && has_moved[1] == false)
				{
					obroty[1]++;
					has_moved[1] = true;
				}
				if (k > 2)
				{
					bool has_notched1 = false, will_notch1 = false;
					int index1 = ((start[1] + obroty[1] - 1) % n) + 1;
					int index2 = ((start[2] + obroty[2] - 1) % n) + 1;

					for (int j = 0; j < no_notches1; j++)
					{
						if ((index1 == maszyna_wir[1].notches[j]) && obroty[1] > 1 && has_moved[1] == true)
						{
							has_notched1 = true;
						}
					}
					if (has_notched1 == true)
					{
						for (int i = 0; i < no_notches2; i++)
						{
							if (index2 == maszyna_wir[2].notches[i])
							{
								double_step = true; break;
							}
						}
					}
					int index1_next = (index1 % n) + 1;

					for (int j = 0; j < no_notches1; j++)
					{
						if ((index1_next == maszyna_wir[1].notches[j]) && obroty[1] > 0)
							will_notch1 = true;
					}
					if (has_moved[1] == true && has_moved[2] == true)
					{
						double_step = false;
					}
					if (has_moved[1] == true && will_notch1 == true)
					{
						double_step = true;
					}
				}
			}
			x = letter - 1;
			for (int i = 0; i < k; i++)
			{
				if (i == 0)
				{
					x = start[0] + obroty[0] + x - 1;
				}
				else
				{
					x = 2 * n + start[i] + (obroty[i] % n) + x - start[i - 1] - (obroty[i - 1] % n) - 1;
				}
				x = (x % n) + 1;
				x = maszyna_wir[i].alf.litery[x];
			}
			x = x - start[k - 1] - (obroty[k - 1] % n) + 2 * n;
			x = (x % n) + 1;

			x = maszyna_ref.alf.litery[x];
			x = n + x + start[k - 1] + obroty[k - 1] - 2;
			x = (x % n) + 1;

			for (int i = k - 1; i >= 0; i--)
			{
				x = x - 1;
				x = (x % n) + 1;
				x = wirnik_o[i].alf.litery[x];

				if (i == 0)
				{
					x = x - (start[0] % n) - (obroty[0] % n) + 2 * n;
				}
				else
				{
					x = x - start[i] - (obroty[i] % n) + start[i - 1] + (obroty[i - 1] % n) + 2 * n;
				}
			}
			x = (x % n) + 1;
			printf("%d ", x);
			scanf("%d", &letter);
		}
		printf("\n");

		zwolnij_po_zadaniu(maszyna_wir, wirnik_o, maszyna_ref, start,  obroty, k);	
	}
	
	zwolnij_na_koniec(wirniki, reflektory, l, m);
	
	
	
	return 0;
}