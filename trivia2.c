#include<ncurses.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define width 30
#define height 10
#define BUFFER 1001

void golire()//functia de golire a ecranului principal pentru a afisa altul
{	WINDOW *nou;
	nou = newwin(100, 120, 0, 0);
	wrefresh(nou);
	delwin(nou);


}
void timp()//functia de afisare a timpului
{	WINDOW *ceas;
	ceas = newwin(1, 20, 0, 0);
	time_t x;
	struct tm * ora;

	time ( &x );
	ora  = localtime ( &x );
	mvwprintw(ceas, 0, 0, "%s", asctime(ora));
	wrefresh(ceas);
	delwin (ceas);

}

void printare(WINDOW *men, int highl, int n_choices, char *meniu[], int startx, int starty, int terminat)//functia de printare a meniului
{
	int x, y, i;
	wbkgd(men, COLOR_PAIR(1));
	x = 2;
	y = 2;
	for (i = 0; i < n_choices; i++)
	{	if (highl == i + 1)
		{	wattron(men, A_REVERSE);
			mvwprintw(men, y, x, "%s", meniu[i]);
			wattroff(men, A_REVERSE);
		}
		else
		{
			wattron(men, COLOR_PAIR(1));
			mvwprintw(men, y, x, "%s", meniu[i]);
			wattroff(men, COLOR_PAIR(1));
		}
		y++;
	}

	wrefresh(men);

}
int ajut(int lungime, int latime , int x, int y, int p, int n, int m, int ramas)//functia de ajutor in cazul apasarii tastei h
{	WINDOW *var1, *var2;//cele 2 variante care vor fi taiate
	int cas1 = n, cas2 = m, r, i, k = 0;
	srand(time(NULL));
	if (cas1 == 0 && cas2 == 0)//crearea unui numar aleator pentru cas1 si cas2 pentru a acoperi casutele
		while (cas1 == cas2 || cas1 == p || cas2 == p)
		{
			r = rand();
			r = r % 4 + 1;
			cas1 = r;

			r = rand();
			r = r % 4 + 1;
			cas2 = r;
		}


	if (ramas)//ramas este folosit pentru a verifica daca s-a marit casuta intrebarii in cazul aceasta avut o intrebare prea mare si i s-au modificat dimensiunile
		//in for se cauta numarul intrebarii pentru a o acoperi
	{	for (i = 1; i <= 4; i++)
		{	if (i == 1 && cas1 == i)
			{
				var1 = newwin(lungime, latime, y + 5, x - 20);
				wrefresh(var1);

			}	if (i == 2 && cas1 == i)
			{
				var1 = newwin(lungime, latime, y + 5, x + 10);
				wrefresh(var1);

			}	if (i == 3 && cas1 == i)
			{
				var1 = newwin(lungime, latime, y + 10 + ramas, x - 20);
				wrefresh(var1);

			}	if (i == 4 && cas1 == i)
			{
				var1 = newwin(lungime, latime, y + 10 + ramas, x + 10);
				wrefresh(var1);

			}
		}
		for (i = 1; i <= 4; i++)
		{	if (i == 1 && cas2 == i)
			{
				var2 = newwin(lungime, latime, y + 5, x - 20);
				wrefresh(var2);

			}	if (i == 2 && cas2 == i)
			{
				var2 = newwin(lungime, latime, y + 5, x + 10);
				wrefresh(var2);

			}	if (i == 3 && cas2 == i)
			{
				var2 = newwin(lungime, latime, y + 10 + ramas, x - 20);
				wrefresh(var2);

			}	if (i == 4 && cas2 == i)
			{
				var2 = newwin(lungime, latime, y + 10 + ramas, x + 10);
				wrefresh(var2);

			}
		}
	} else
	{	for (i = 1; i <= 4; i++)
		{	if (i == 1 && cas1 == i)
			{
				var1 = newwin(lungime, latime, y + 5, x - 20);
				wrefresh(var1);

			}	if (i == 2 && cas1 == i)
			{
				var1 = newwin(lungime, latime, y + 5, x + 10);
				wrefresh(var1);

			}	if (i == 3 && cas1 == i)
			{
				var1 = newwin(lungime, latime, y + 10, x - 20);
				wrefresh(var1);

			}	if (i == 4 && cas1 == i)
			{
				var1 = newwin(lungime, latime, y + 10, x + 10);
				wrefresh(var1);

			}
		}
		for (i = 1; i <= 4; i++)
		{	if (i == 1 && cas2 == i)
			{
				var2 = newwin(lungime, latime, y + 5, x - 20);
				wrefresh(var2);

			}	if (i == 2 && cas2 == i)
			{
				var2 = newwin(lungime, latime, y + 5, x + 10);
				wrefresh(var2);

			}	if (i == 3 && cas2 == i)
			{
				var2 = newwin(lungime, latime, y + 10, x - 20);
				wrefresh(var2);

			}	if (i == 4 && cas2 == i)
			{
				var2 = newwin(lungime, latime, y + 10, x + 10);
				wrefresh(var2);

			}
		}
	}
	if (cas1 > cas2)
		k = cas1 * 10 + cas2;
	else k = cas2 * 10 + cas1;
	return k;
}

void intrebare(WINDOW *intr, int y, int x, char buffer[], FILE *dest, char *argv[], int highl1, int nr, int punct, int v[])
{	WINDOW *raspuns1, *raspuns2, *raspuns3, *raspuns4, *scor;
	int lungime = 5, latime = 30, i = 1, n, marime = 0, ramas = 0, m = x, p = y, retur = 0;
	intr = newwin(5, 60, (y - 5) / 2, (x - 40) / 2 - latime + 10);
	scor = newwin(15, latime, (y - 5) / 2, (x - 40) / 2 + 2 * latime + 1 - 20);
	box(scor, 0, 0);
	mvwprintw(scor, 2, 2, "Scorul este: ");
	mvwprintw(scor, 2, 16, "%d", punct);
	mvwprintw(scor, 3, 1, "-----------------------");
	mvwprintw(scor, 5, 2, "Control");
	mvwprintw(scor, 7, 2, "Enter - selectare");
	mvwprintw(scor, 8, 2, "k - skip");
	mvwprintw(scor, 9, 2, "h - ajutor");
	mvwprintw(scor, 10, 2, "q - exit");
	wrefresh(scor);
	box(intr, 0, 0);
	wrefresh(intr);
	keypad(intr, TRUE);
	raspuns1 = newwin(lungime, latime, (y - 5) / 2 + 5, (x - 40) / 2 - 20);

	wbkgd(raspuns1, COLOR_PAIR(7));
	wrefresh(raspuns1);
	raspuns2 = newwin(lungime, latime, (y - 5) / 2 + 5, (x - 40) / 2 + 10);

	wbkgd(raspuns2, COLOR_PAIR(8));
	wrefresh(raspuns2);
	raspuns3 = newwin(lungime, latime, (y - 5) / 2 + 10, (x - 40) / 2 - 20);
	wbkgd(raspuns3, COLOR_PAIR(9));
	wrefresh(raspuns3);
	raspuns4 = newwin(lungime, latime, (y - 5) / 2 + 10, (x - 40) / 2 + 10);
	wbkgd(raspuns4, COLOR_PAIR(2));
	wrefresh(raspuns4);
	v[3] = (y - 5) / 2;
	v[4] = (x - 40) / 2;

	dest = fopen(argv[nr], "r+");
	fgets(buffer, BUFFER, dest);
	fgets(buffer, BUFFER, dest);
	mvwprintw(intr, 2, (55 - strlen(buffer)) / 2, "%s", buffer);
	box(intr, 0, 0);
	wrefresh(intr);
	while (i <= 5)
	{	fgets(buffer, BUFFER, dest);
		if (strlen(buffer) < ((lungime - 2) * (latime - 2)))
		{	if (i == 1)
			{
				if (strlen(buffer) > latime)
				{
					x = 1;
					y = 1;
				}
				else
				{
					x = (20 - strlen(buffer)) / 2;
					y = 2;
				}
				if (highl1 == i)
				{
					wbkgd(raspuns1, COLOR_PAIR(7));
					wrefresh(raspuns1);
					wattron(raspuns1, A_REVERSE);
					mvwprintw(raspuns1, y, x, "%s", buffer);
					wattroff(raspuns1, A_REVERSE);
				}
				else
					mvwprintw(raspuns1, y, x, "%s", buffer);


				wrefresh(raspuns1);
			}

			else if (i == 2)
			{
				if (strlen(buffer) > latime)
				{
					x = 1;
					y = 1;
				}
				else
				{
					x = (20 - strlen(buffer)) / 2;
					y = 2;
				}
				if (highl1 == i)

				{
					wbkgd(raspuns2, COLOR_PAIR(8));
					wrefresh(raspuns2);
					wattron(raspuns2, A_REVERSE);
					mvwprintw(raspuns2, y, x, "%s", buffer);
					wattroff(raspuns2, A_REVERSE);
				}
				else
					mvwprintw(raspuns2, y, x, "%s", buffer);
				wrefresh(raspuns2);
			}
			else if (i == 3)
			{
				if (strlen(buffer) > latime)
				{
					x = 1;
					y = 1;
				}
				else
				{
					x = (20 - strlen(buffer)) / 2;
					y = 2;
				}
				if (highl1 == i)
				{
					wbkgd(raspuns3, COLOR_PAIR(9));
					wrefresh(raspuns3);
					wattron(raspuns3, A_REVERSE);
					mvwprintw(raspuns3, y, x, "%s", buffer);
					wattroff(raspuns3, A_REVERSE);
				}

				else

					mvwprintw(raspuns3, y, x, "%s", buffer);


				wrefresh(raspuns3);
			}
			else if (i == 4)
			{
				if (strlen(buffer) > latime)
				{
					x = 1;
					y = 1;
				}
				else
				{
					x = (20 - strlen(buffer)) / 2;
					y = 2;
				}
				if (highl1 == i)
				{
					wbkgd(raspuns4, COLOR_PAIR(2));
					wrefresh(raspuns4);
					wattron(raspuns4, A_REVERSE);
					mvwprintw(raspuns4, y, x, "%s", buffer);
					wattroff(raspuns4, A_REVERSE);
				}
				else

					mvwprintw(raspuns4, y, x, "%s", buffer);


				wrefresh(raspuns4);
			}
			i++;
		}
		else
		{	while (strlen(buffer) >= ((lungime - 2) * (latime - 2)))
			{	lungime++;
				ramas++;

			}
			delwin(raspuns1);
			delwin(raspuns2);
			delwin(raspuns3);
			delwin(raspuns4);
			raspuns1 = newwin(lungime, latime, (p - 5) / 2 + 5, (m - 40) / 2 - 20);

			wbkgd(raspuns1, COLOR_PAIR(7));
			wrefresh(raspuns1);
			raspuns2 = newwin(lungime, latime, (p - 5) / 2 + 5, (m - 40) / 2 + 10);

			wbkgd(raspuns2, COLOR_PAIR(8));
			wrefresh(raspuns2);
			raspuns3 = newwin(lungime, latime, (p - 5) / 2 + 10 + ramas, (m - 40) / 2 - 20);
			wbkgd(raspuns3, COLOR_PAIR(9));
			wrefresh(raspuns3);
			raspuns4 = newwin(lungime, latime, (p - 5) / 2 + 10 + ramas, (m - 40) / 2 + 10);
			wbkgd(raspuns4, COLOR_PAIR(2));
			wrefresh(raspuns4);
			dest = fopen(argv[nr], "r+");
			fgets(buffer, BUFFER, dest);
			fgets(buffer, BUFFER, dest);
			i = 1;
			v[3] = (p - 5) / 2;



		}

	}
	delwin(intr);
	delwin(scor);
	v[1] = lungime;
	v[2] = latime;
	v[5] = ramas;





}

int main(int argc, char *argv[])
{	if(argc==1)
	{
		printf("Eroare nu s-au dat argumente in linia de comanda\n");
		return 1;
	}
	int startx = 0, starty = 0, alegeri = 2, y = 30, x = 90;
	char *meniu[] = {"New Game",
	                 "Quit",
	                 "Resume Game"	
	                };
	int highl = 1, highl1 = 1, i = 1, ramas = 1, ramas2 = 1, p = 0, punct = 0, ajutor = 0, ajutor1 = 0, ajutor2 = 0;
	//highl reprezinta variabila care este aleasa
	//punct reprezinta punctajul
	//ramas2 verifica daca s-a apasat tasta q pentru a iesi din joc si sa apara resume
	char buffer[BUFFER];
	WINDOW *men, *ecr, *intr, *trivia, *ro1, *ro2, *ro3;
	int x1, y1, v[6];
	int k = 0, c, nimic, nr1, nr2, aux, j, sparg = 0, terminat = 0, skip = 1, corect = 0, gresit = 0, lungime1, latime1, help = 0;
	//Skip se foloseste pentru a verifica daca optiunea de skip mai este valabila, 0 inseamna ca s-a folosit, 1 ca nu.
	//Corect reprezinta numarul de intrebari corecte la care s-a raspuns iar gresit reprezinta numarul de intrebari gresite.
	//k se foloseste pentru a verifica ce tasta s-a apasat(enter, stanga,dreapta,h,q,k)
	//lungime1 si latime1 sunt folosite pentru lungimea casutelor de raspunsuri
	

	FILE *dest;
	dest = fopen(argv[1], "r+");
	initscr();
	clear();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);

	ecr = newwin(1, 33, 0, 0);
	ro1 = newwin(y / 3, x + 20, 0, 0);
	ro2 = newwin(y / 3, x + 20, y / 3, 0);
	ro3 = newwin(y / 3, x + 20, 2 * y / 3, 0);

	startx = (x - width) / 2;
	starty = (y - height) / 2;
	men = newwin(height, width, starty, startx);
	use_default_colors();
	start_color();//intializarea perechilor de culori
	init_pair(1, COLOR_WHITE, COLOR_YELLOW);
	init_pair(2, COLOR_WHITE, COLOR_RED);
	init_pair(3, COLOR_WHITE, COLOR_BLUE);
	init_pair(4, -1, COLOR_RED);
	init_pair(5, -1, COLOR_YELLOW);
	init_pair(6, -1, COLOR_BLUE);
	init_pair(7, COLOR_WHITE, COLOR_GREEN);
	init_color(COLOR_CYAN, 300, 120, 190);
	init_pair(8, COLOR_WHITE, COLOR_CYAN);
	init_color(COLOR_MAGENTA, 200, 230, 300);
	init_pair(9, COLOR_WHITE, COLOR_MAGENTA);

	keypad(men, TRUE);
	trivia = newwin(5, 66, 22, 10);
	wattron(ro1, COLOR_PAIR(4));
	wattron(ro2, COLOR_PAIR(5));
	wattron(ro3, COLOR_PAIR(6));
	wbkgd(ro1, COLOR_PAIR(4));
	wbkgd(ro2, COLOR_PAIR(5));
	wbkgd(ro3, COLOR_PAIR(6));

	while (1)
	{

		if (terminat == argc - 1)
		{
			ajutor = 0;
			skip = 1;
			terminat = 0;
			golire();
			//initierea ecranului de final
			WINDOW *final;
			final = newwin(30, 90, 0, 0);
			keypad(final, TRUE);
			mvwprintw(final, 0, 0, "Scor final:%d", punct);
			mvwprintw(final, 1, 0, "Intrebari corecte:%d", corect);
			mvwprintw(final, 2, 0, "Intrebari gresite:%d", gresit);
			wrefresh(final);
			wgetch(final);
			golire();
			delwin(men);
			men = newwin(height, width, starty, startx);
			highl = 1;

			wrefresh(ro1);
			wrefresh(ro2);
			wrefresh(ro3);
			wattron(ecr, COLOR_PAIR(2));
			mvwprintw(ecr, 0, 0, "Foloseste sagetile ca sa te misti");
			wattroff(ecr, COLOR_PAIR(2));

			wbkgd(ecr, COLOR_PAIR(1));
			wrefresh(ecr);
			printare(men, highl, alegeri, meniu, startx, starty, terminat);

			wattron(trivia, COLOR_PAIR(3));
			mvwprintw(trivia, 0, 0, " ////////    //////    ///  ///        ///    ///      ///        ");
			mvwprintw(trivia, 1, 0, "   ////     /     //         ///      ///            ///  ///     ");
			mvwprintw(trivia, 2, 0, "   ////     //////     //     ///    ///      //    //////////    ");
			mvwprintw(trivia, 3, 0, "   ////     //  //     //       //   //       //   ///      ///   ");
			mvwprintw(trivia, 4, 0, "   ////     //   //    //         //          //   ///      ///   ");
			wrefresh(trivia);
			wattroff(trivia, COLOR_PAIR(3));



			keypad(men, TRUE);
			alegeri = 2;
		}
		golire();
		wbkgd(ro1, COLOR_PAIR(4));
		wbkgd(ro2, COLOR_PAIR(5));
		wbkgd(ro3, COLOR_PAIR(6));
		wrefresh(ro1);
		wrefresh(ro2);
		wrefresh(ro3);

		wattron(trivia, COLOR_PAIR(3));
		mvwprintw(trivia, 0, 0, " ////////    //////    ///  ///        ///    ///      ///        ");
		mvwprintw(trivia, 1, 0, "   ////     /     //         ///      ///            ///  ///     ");
		mvwprintw(trivia, 2, 0, "   ////     //////     //     ///    ///      //    //////////    ");
		mvwprintw(trivia, 3, 0, "   ////     //  //     //       //   //       //   ///      ///   ");
		mvwprintw(trivia, 4, 0, "   ////     //   //    //         //          //   ///      ///   ");
		wrefresh(trivia);
		wattroff(trivia, COLOR_PAIR(3));

		wattron(ecr, COLOR_PAIR(2));
		mvwprintw(ecr, 0, 0, "Foloseste sagetile ca sa te misti");
		wattroff(ecr, COLOR_PAIR(2));



		wrefresh(ecr);


		printare(men, highl, alegeri, meniu, startx, starty, terminat);

		c = wgetch(men);
		switch (c)
		{
		case KEY_UP:
			if (highl == 1)
				highl = alegeri;
			else highl--;
			break;
		case KEY_DOWN:
			if (highl == alegeri)
				highl = 1;
			else highl++;
			break;
		case 10:
			if (highl == 1)
			{
				terminat = 0;
				punct = 0;
				ajutor = 0;
				ramas = 1;
				sparg = 0;
				skip = 1;
				corect = 0;
				gresit = 0;
				k = 0;
				alegeri = 2;
				//se alege vaianta de new game si se reinitializeaza toate valorile variabilelor cu cele initiale


				for (i = 1; i <= argc - 1; i++)
				{
					while (1)
					{
						golire();
						intrebare(intr, y, x, buffer, dest, argv, highl1, i, punct, v);
						timp();
						c = wgetch(men);


						switch (c)
						{
						case KEY_LEFT:
							if (highl1 == 1)
								highl1 = 4;
							else highl1--;
							break;
						case KEY_RIGHT:

							if (highl1 == 4)

								highl1 = 1;

							else

								highl1++;

							break;

						case 107:// apas k pt skip;

							if (i == argc - 1 && skip != 0)
							{
								k = 3;
								skip = 0;
								corect++;
								punct += 10;
								break;
							}
							else if (skip)
							{
								skip = 0;
								i++;
								corect++;
								terminat++;
								punct += 10;
								break;
							}
							else break;
						case 10:
							terminat++;
							k = 1;
							p = atoi(buffer);
							if (p == highl1)
							{
								punct += 10;
								corect++;
							}
							else {
								punct = punct - 5;
								gresit++;
							}
							break;
						case 104://apas h pt ajutor
							if (ajutor)
								break;
							else {
								p = atoi(buffer);//p este numarul intrebarii corecte
								ajutor = 1;
								golire();
								intrebare(intr, y, x, buffer, dest, argv, highl1, i, punct, v);//cu ajutorul vectorului v se verifica daca s-a modificat dimensiunea casutelor
								lungime1 = v[1];
								latime1 = v[2];
								x1 = v[4];
								y1 = v[3];
								ajutor1 = ajut(lungime1, latime1, x1, y1, p, 0, 0, v[5]);
								ajutor2 = ajutor1 % 10;//in ajutor1 si ajutor2 se obtin cele 2 variante care vor fi eliminate din selectie
								ajutor1 = ajutor1 / 10;
								for (j = 1; j <= 4; j++)
									if (j != ajutor1 && j != ajutor2)
										nr1 = j;
								for (j = 1; j <= 4; j++)
									if (j != ajutor1 && j != ajutor2 && j != nr1)
										nr2 = j;
								if (nr2 > nr1)
								{
									aux = nr1;
									nr1 = nr2;
									nr2 = aux;
								}

								highl1 = nr1;//highl1 reprezinta noul highlight pentru selectarea optiuniii
								intrebare(intr, y, x, buffer, dest, argv, highl1, i, punct, v);
								nimic = ajut(lungime1, latime1, x1, y1, p, ajutor1, ajutor2, v[5]);//nimic e folosit doar pentru afisarea ecranului final acoperit
								while (1)
								{	timp();
									c = wgetch(men);
									switch (c)
									{
									case KEY_LEFT:
										if (highl1 == nr2)
											highl1 = nr1;
										else highl1 = nr2;

										break;
									case KEY_RIGHT:
										if (highl1 == nr1)
											highl1 = nr2;
										else highl1 = nr1;
										break;
									case 107:// apas k pt skip;
										if (i == argc - 1 && skip != 0)
										{
											k = 3;
											corect++;
											skip = 0;
											punct += 10;
											break;
										}
										if (skip)
										{
											skip = 0;
											corect++;
											i++;
											terminat++;
											punct += 10;
											break;
										}
										else break;
									case 113://apas q ca sa ies
										k = 2;
										help = 1;
										break;
									case 10:
										terminat++;
										k = 1;
										if (p == highl1)
										{
											punct += 10;
											corect++;
										}
										else {
											punct = punct - 5;
											gresit++;
										}
										sparg = 1;
										break;

									}	golire();
									intrebare(intr, y, x, buffer, dest, argv, highl1, i, punct, v);
									lungime1 = v[1];
									latime1 = v[2];
									x1 = v[4];
									y1 = v[3];
									nimic = ajut(lungime1, latime1, x1, y1, p, ajutor1, ajutor2, v[5]); //nimic este folosit doar pentru a apela functia ajut pentru a se pastra acoperite ecranele

									if (sparg || k == 2)
										break;

								}
								if (sparg || k == 2)
									break;
							}

						case 113://apas q ca sa ies
							k = 2;
							break;


						}
						if (k == 0)
						{	golire();
							intrebare(intr, y, x, buffer, dest, argv, highl1, i, punct, v);
							timp();
						} else if (k == 1)
						{
							k = 0;
							break;
						}
						else if (k == 2)
						{
							alegeri = 3;
							k = 0;
							ramas2 = i + 1;
							break;

						}
						else if (k == 3)
						{
							terminat++;
							break;
						}

					}
					if (ramas2 != 1)
					{
						ramas2 = 1;
						ramas = i;
						break;
					}
				}
			}
			else if (highl == 3) //se alege varianta de resume pentru a continua jocul
			{
				for (i = ramas; i <= argc - 1; i++)

					if (help) //daca a fost apasat quit in timp ce era activa optiunea de help se vor pastra doar cele 2 variante in loc sa fie afisate toate 4

					{
						golire();
						intrebare(intr, y, x, buffer, dest, argv, highl1, i, punct, v);
						nimic = ajut(lungime1, latime1, x1, y1, p, ajutor1, ajutor2, v[5]);
						help = 0;
						while (1)
						{timp();
							c = wgetch(men);
							switch (c)
							{
							case KEY_LEFT:
								if (highl1 == nr2)
									highl1 = nr1;
								else highl1 = nr2;

								break;
							case KEY_RIGHT:
								if (highl1 == nr1)
									highl1 = nr2;
								else
									highl1 = nr1;
								break;
							case 107:// apas k pt skip;
								if (i == argc - 1 && skip != 0)
								{
									k = 3;
									corect++;
									skip = 0;
									break;
								}
								if (skip)
								{
									skip = 0;
									corect++;
									i++;
									terminat++;
									break;
								}
								else break;
							case 113://apas q ca sa ies
								k = 2;
								help = 1;
								break;

							case 10:
								terminat++;
								k = 1;
								if (p == highl1)
								{
									punct += 10;
									corect++;
								}
								else
								{
									punct = punct - 5;
									gresit++;
								}
								sparg = 1;
								break;

							}

							golire();
							intrebare(intr, y, x, buffer, dest, argv, highl1, i, punct, v);
							lungime1 = v[1];
							latime1 = v[2];
							x1 = v[4];
							y1 = v[3];
							nimic = ajut(lungime1, latime1, x1, y1, p, ajutor1, ajutor2, v[5]);

							if (sparg || k == 2)
								break;

						}


					}



					else
					{	//se joaca jocul in continuarea celui precedent la fel ca in new game fara a initia variabilele cu valorile initiale
						golire();
						intrebare(intr, y, x, buffer, dest, argv, highl1, i, punct, v);
						while (1)
						{	timp();
							c = wgetch(men);
							switch (c)
							{
							case KEY_LEFT:

								if (highl1 == 1)
									highl1 = 4;
								else
									highl1--;
								break;

							case KEY_RIGHT:

								if (highl1 == 4)
									highl1 = 1;
								else
									highl1++;
								break;

							case 107:// apas k pt skip;

								if (i == argc - 1 && skip != 0)//in cazul in care se da skip la ultima intrebare
								{
									k = 3;
									corect++;
									skip = 0;
									break;
								}
								else if (skip)//skip pentru orice intrebare
								{
									skip = 0;
									corect++;
									i++;
									terminat++;
									break;
								}
								else break;

							case 104://apas h pt ajutor
								if (ajutor)
									break;
								else {
									p = atoi(buffer);
									ajutor = 1;
									golire();
									intrebare(intr, y, x, buffer, dest, argv, highl1, i, punct, v);
									lungime1 = v[1];
									latime1 = v[2];
									x1 = v[4];
									y1 = v[3];
									ajutor1 = ajut(lungime1, latime1, x1, y1, p, 0, 0, v[5]);
									ajutor2 = ajutor1 % 10;
									ajutor1 = ajutor1 / 10;
									for (j = 1; j <= 4; j++)
										if (j != ajutor1 && j != ajutor2)
											nr1 = j;
									for (j = 1; j <= 4; j++)
										if (j != ajutor1 && j != ajutor2 && j != nr1)
											nr2 = j;
									if (nr2 > nr1)
									{
										aux = nr1;
										nr1 = nr2;
										nr2 = aux;
									}

									highl1 = nr1; //highl1 devine noua variabila de selectare a variantei in cazul activarii optiunii de ajutor
									while (1)
									{	timp();
										c = getch();
										switch (c)
										{
										case KEY_LEFT:

											if (highl1 == nr2)
												highl1 = nr1;
											else
												highl1 = nr2;
											break;

										case KEY_RIGHT:

											if (highl1 == nr1)
												highl1 = nr2;
											else
												highl1 = nr1;
											break;
										case 107:// apas k pt skip;
											if (i == argc - 1 && skip != 0)
											{
												k = 3;
												corect++;
												skip = 0;
												punct +=10;
												break;
											}
											if (skip)
											{
												skip = 0;
												corect++;
												i++;
												terminat++;
												punct +=10;
												break;
											}
											else break;
										case 10:

											terminat++;
											k = 1;
											if (p == highl1)
											{
												punct += 10;
												corect++;
											}
											else {
												punct = punct - 5;
												gresit++;
											}
											sparg = 1;
											break;

										}
										golire();
										intrebare(intr, y, x, buffer, dest, argv, highl1, i, punct, v);
										lungime1 = v[1];
										latime1 = v[2];
										x1 = v[4];
										y1 = v[3];
										nimic = ajut(lungime1, latime1, x1, y1, p, ajutor1, ajutor2, v[5]);
										if (sparg)
											break;
									}
									if (sparg)
										break;
								}

							case 113://apas q ca sa ies
								k = 2;
								break;
							case 10:

								terminat++;
								k = 1;
								p = atoi(buffer);
								if (p == highl1)
								{
									punct += 10;
									corect++;
								}
								else
								{
									punct = punct - 5;
									gresit++;
								}
								break;


							} if (k == 0)
							{	golire();
								intrebare(intr, y, x, buffer, dest, argv, highl1, i, punct, v);
							}
							else if (k == 1)
							{
								alegeri = 2; k = 0;
								break;
							}
							else if (k == 2)
							{
								alegeri = 3;
								k = 0;
								ramas2 = i + 1;
								break;

							}
							else if (k == 3)
							{
								terminat++;
								k = 0;
								break;
							}

						}

						if (ramas2 != 1)
						{
							ramas2 = 1;
							ramas = i;
							break;
						}

						else if (k == 3 && terminat == argc - 1)
						{
							alegeri = 2;
							break;
						}
						else if (k == 3)
							break;
					}
			}
			else if (highl == 2)
			{
				endwin();
				return 0;
			}

			break;
		}

		golire();

		wrefresh(ro1);
		wrefresh(ro2);
		wrefresh(ro3);
		wattron(ecr, COLOR_PAIR(2));
		mvwprintw(ecr, 0, 0, "Foloseste sagetile ca sa te misti");
		wattroff(ecr, COLOR_PAIR(2));
		wrefresh(ecr);
		printare(men, highl, alegeri, meniu, startx, starty, terminat);

		wattron(trivia, COLOR_PAIR(3));
		mvwprintw(trivia, 0, 0, " ////////    //////    ///  ///        ///    ///      ///        ");
		mvwprintw(trivia, 1, 0, "   ////     /     //         ///      ///            ///  ///     ");
		mvwprintw(trivia, 2, 0, "   ////     //////     //     ///    ///      //    //////////    ");
		mvwprintw(trivia, 3, 0, "   ////     //  //     //       //   //       //   ///      ///   ");
		mvwprintw(trivia, 4, 0, "   ////     //   //    //         //          //   ///      ///   ");
		wrefresh(trivia);
		wattroff(trivia, COLOR_PAIR(3));
		//reprintarea meniului initial de new game
	}



	endwin();
	return 0;

}

