/**
 * @file main.c
 * @author Daniel Cieslak
 * @brief Glowny plik wykonawczy programu.
 * Zawiera cala funkcjonalnosc programu.
**/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
/**
*Zdefiniowanie typu bazowego struktury dynamicznej - dwukierunkowej listy liniowej o nazwie listElement
**/
typedef struct phoneList{
    unsigned int iD;                                                /**< Zmienna typu unsigned int zawieraja numer id w ksiazke telefonicznej */
    char firstName[50];                                             /**< Tablica znakow zawierajaca imie */
    char lastName[50];                                              /**< Tablica znakow zawierajca nazwisko */
    char streetName[50];                                            /**< Tablica znakow zawierajaca nazwe ulicy */
    unsigned int streetNumber;                                      /**< Zmienna typu usnigned int zawierajaca numer domu */
    unsigned int postcode;                                          /**< Zmienna typu unsigned int zawierajaca kod pocztowy */
    char city[50];                                                  /**< Tablica znakow zawierajaca nazwe miasta */
    unsigned long long int phoneNumber;                             /**< Zmienna typu long long int zawierajaca numer telefonu */
    struct phoneList *prev;                                         /**< Rekurencyjne deklaracja tej samej struktury, lecz zmienna jest wzkaznikiem na element poprzedni listy */
    struct phoneList *next;                                         /**< Rekurencyjne deklaracja tej samej struktury, lecz zmienna jest wzkaznikiem na element nastepny listy */
}listElement;
/**
*@brief Funkcja odpowiedzialna za pobranie danych z pliku i zapisaniu ich do listy
*@param *dataFile to wzkaznik na plik, z ktorego beda pobierane dane do listy
*@param **head to podwojny wzkaznik na aktualnie ostatni element listy
*@param idn to licznik do autonumerowania wartosci id w liscie
**/
void dataFromFile(FILE *dataFile, listElement **head, int idn){     /** Deklaracja funkcji dataFromFile przyjmujacej jako argumenty wzkaznik na plik, podwojny wzkaznik typu struktury listElement, oraz zmienna typu int bedaca licznikiem id do autonumerowania kolejnych elementow wierszy ksiazki telefonicznej*/
    char charc[50];
    char charc2[50];
    if(*head==NULL) {                                               /** Warunek sprawdzający czy istnieje pierwszy element listy */
    	*head=(listElement *)malloc(sizeof(listElement));           /** Alokacja pamieci na pierwszy element listy */
        fscanf(dataFile,"%d\n",&(*head)->iD);                       /** Wywolanie funkcji fscanf ktora odpowiada za wczytanie linii z pliku i zapisanie jej do pola iD pierwszego elementu listy */
        (*head)->iD=idn;                                            /** Przypisanie polu iD pierwszego elementu listy wartosci zmiennej idn */
   		fscanf(dataFile,"%s\n",&(*head)->firstName);                /** Wywolanie funkcji fscanf ktora odpowiada za wczytanie linii z pliku i zapisanie jej do pola firstName pierwszego elementu listy */
        fscanf(dataFile,"%s\n",&(*head)->lastName);                 /** Wywolanie funkcji fscanf ktora odpowiada za wczytanie linii z pliku i zapisanie jej do pola lastName pierwszego elementu listy */
        fgets(charc,50,dataFile);                                   /** Wywolanie funkcji fgets ktora odpowiada za wczytanie linii z pliku i zapisanie jej do tablicy charc */
        charc[strcspn(charc, "\n")] = 0;                            /** Funkcja strcspn szuka w tablicy znak konca linii nastepnie zwraca jego indeks, ktory pozniej sluzy do tego aby znak konca linii zastapic zerem */
        for(int i=0; i<50; i++)                                     /** Petla for wykonujaca sie 50 razy */
            (*head)->streetName[i]=charc[i];                        /** Kazdemu elementowi tablicy streetName pierwszego elementu listy przypisywany jest kolejny element tablicy charc */
        fscanf(dataFile,"%d\n",&(*head)->streetNumber);             /** Wywolanie funkcji fscanf ktora odpowiada za wczytanie linii z pliku i zapisanie jej do pola streetNumber pierwszego elementu listy */
   		fscanf(dataFile,"%d\n",&(*head)->postcode);                 /** Wywolanie funkcji fscanf ktora odpowiada za wczytanie linii z pliku i zapisanie jej do pola postcode pierwszego elementu listy */
   		fgets(charc2,50,dataFile);                                  /** Wywolanie funkcji fgets ktora odpowiada za wczytanie linii z pliku i zapisanie jej do tablicy charc2 */
        charc2[strcspn(charc2, "\n")] = 0;                          /** Funkcja strcspn szuka w tablicy znak konca linii nastepnie zwraca jego indeks, ktory pozniej sluzy do tego aby znak konca linii zastapic zerem */
        for(int i=0; i<50; i++)                                     /** Petla for wykonujaca sie 50 razy */
            (*head)->city[i]=charc2[i];                             /** Kazdemu elementowi tablicy city pierwszego elementu listy przypisywany jest kolejny element tablicy charc2 */
        fscanf(dataFile,"%llu\n",&(*head)->phoneNumber);            /** Wywolanie funkcji fscanf ktora odpowiada za wczytanie linii z pliku i zapisanie jej do pola phoneNumber pierwszego elementu listy */
   		(*head)->prev = NULL;                                       /** Wzkaznikowi na element poprzedni pierwszego elementu listy zostaje przypisana wartosc NULL*/
    	(*head)->next = NULL;                                       /** Wzkaznikowi na element nastepny pierwszego elementu listy zostaje przypisana wartosc NULL*/
	} else {                                                        /** Przejscie do alternatywnych intrukcji w przypadku niespelnienia warunku */
            listElement *curr=*head;                                /** Deklaracja wzkaznika na element aktualny listy i prypisanie mu wartosci wzkaznika na pierwszy element listy  */
            listElement *newElement;
            while (curr->next!=NULL) {                              /** Petla while dzialajaca do momentu az pole nastepne w aktualnej strukturze bedzie rowne NULL */
                curr = curr->next;                                  /** Przypisanie aktualnemu elementowi listy wartosci pola nastepnego w aktualnym elemencie listy */
            }
            curr->next = (listElement *)malloc(sizeof(listElement));/** Alokacja pamieci na pole nastepne w aktualnym elemenie listy */
            fscanf(dataFile,"%d\n",&curr->next->iD);                /** Wywolanie funkcji fscanf ktora odpowiada za wczytanie linii z pliku i zapisanie jej do pola iD pola next aktualnego elementu listy */
            curr->next->iD=idn;                                     /** Przypisanie polu id listy wartosci zmiennej idn */
            fscanf(dataFile,"%s\n",&curr->next->firstName);         /** Wywolanie funkcji fscanf ktora odpowiada za wczytanie linii z pliku i zapisanie jej do pola firstName pola next aktualnego elementu listy */
            fscanf(dataFile,"%s\n",&curr->next->lastName);          /** Wywolanie funkcji fscanf ktora odpowiada za wczytanie linii z pliku i zapisanie jej do pola lastName pola next aktualnego elementu listy */
            fgets(charc,50,dataFile);                               /** Wywolanie funkcji fgets ktora odpowiada za wczytanie linii z pliku i zapisanie jej do tablicy charc */
            charc[strcspn(charc, "\n")] = 0;                        /** Funkcja strcspn szuka w tablicy znak konca linii nastepnie zwraca jego indeks, ktory pozniej sluzy do tego aby znak konca linii zastapic zerem */
                for(int i=0; i<50; i++)                             /** Petla for wykonujaca sie 50 razy */
            curr->next->streetName[i]=charc[i];                     /** Kazdemu elementowi tablicy streetName aktualnego elementu listy przypisywany jest kolejny element tablicy charc */
            fscanf(dataFile,"%d\n",&curr->next->streetNumber);      /** Wywolanie funkcji fscanf ktora odpowiada za wczytanie linii z pliku i zapisanie jej do pola streetNumber pola next aktulnego elementu listy */
            fscanf(dataFile,"%d\n",&curr->next->postcode);          /** Wywolanie funkcji fscanf ktora odpowiada za wczytanie linii z pliku i zapisanie jej do pola postcode pola next aktualnego elementu listy */
            fgets(charc2,50,dataFile);                              /** Wywolanie funkcji fgets ktora odpowiada za wczytanie linii z pliku i zapisanie jej do tablicy charc2 */
            charc2[strcspn(charc2, "\n")] = 0;                      /** Funkcja strcspn szuka w tablicy znak konca linii nastepnie zwraca jego indeks, ktory pozniej sluzy do tego aby znak konca linii zastapic zerem */
            for(int i=0; i<50; i++)                                 /** Petla for wykonujaca sie 50 razy */
                curr->next->city[i]=charc2[i];                      /** Kazdemu elementowi tablicy city aktualnego elementu listy przypisywany jest kolejny element tablicy charc2 */
            fscanf(dataFile,"%llu\n",&curr->next->phoneNumber);     /** Wywolanie funkcji fscanf ktora odpowiada za wczytanie linii z pliku i zapisanie jej do pola phoneNumber pola next aktualnego elementu listy */
            curr->next->prev=curr;                                  /** Wzkaznikowi na element poprzedni i nastepny aktualnego elementu listy zostaje przypisana wartosc aktualnego elementu listy */
            curr->next->next = NULL;                                /** Wzkaznikowi na element nastepny nastepnego elementu aktualnego listy zostaje przypisana wartosc NULL */
	}
    return;                                                         /** Funkcja nic nie zwraca */
}
/**
*@brief Funkcja odpowiedzialna za dodawanie nowego elementu na koniec listy
*@param **head to podwojny wzkaznik na aktualnie ostatni element listy
*@param *dataFile to wzkaznik na plik, z ktorego beda pobierane dane do listy
*@param idn to licznik do autonumerowania wartosci id w liscie
**/
void pushNew(listElement **head, FILE *dataFile, int idn){              /** Deklaracja funkcji pushNew przyjmujacej jako argumenty wzkaznik na plik, podwojny wzkaznik typu struktury listElement, oraz zmienna typu int bedaca licznikiem id do autonumerowania kolejnych elementow wierszy ksiazki telefonicznej*/
    long long num=26;
    char charc[50]={NULL};
    if(*head==NULL) {                                                   /** Warunek sprawdzający czy istnieje pierwszy element listy */
    	*head = (listElement *)malloc(sizeof(listElement));             /** Alokacja pamieci na pierwszy element listy */
        (*head)->iD=idn;                                                /** Przypisanie polu iD pierwszego elementu listy wartosci zmiennej idn */
        fprintf(dataFile,"%d\n",num);                                   /** Zapisanie do pliku linijki z polem iD pierwszego elementu listy */
        puts("Write first name:");                                      /** Wyswietlenie komunikatu funkcja puts */
        scanf("%s",&charc);                                             /** Pobranie od uzytkownika ciagu znakow i zapisanie go do zmiennej charc*/
        for(int i=0; i<50; i++)                                         /** Petla for wykonujaca sie 50 razy */
            (*head)->firstName[i]=charc[i];                             /** Kazdemu elementowi tablicy firstName pierwszego elementu listy przypisywany jest kolejny element tablicy charc */
        fprintf(dataFile,"%s\n",charc);                                 /** Zapisanie do pliku linijki z polem firstName pierwszego elementu listy */
        puts("Write last name:");                                       /** Wyswietlenie komunikatu funkcja puts */
        scanf("%s",&charc);                                             /** Pobranie od uzytkownika ciagu znakow i zapisanie go do zmiennej charc*/
        for(int i=0; i<50; i++)                                         /** Petla for wykonujaca sie 50 razy */
            (*head)->lastName[i]=charc[i];                              /** Kazdemu elementowi tablicy lastName pierwszego elementu listy przypisywany jest kolejny element tablicy charc */
        fprintf(dataFile,"%s\n",charc);                                 /** Zapisanie do pliku linijki z polem lastName pierwszego elementu listy */
        puts("Write street name:");                                     /** Wyswietlenie komunikatu funkcja puts */
        scanf("%s",&charc);                                             /** Pobranie od uzytkownika ciagu znakow i zapisanie go do zmiennej charc*/
        for(int i=0; i<50; i++)                                         /** Petla for wykonujaca sie 50 razy */
            (*head)->streetName[i]=charc[i];                            /** Kazdemu elementowi tablicy streetName pierwszego elementu listy przypisywany jest kolejny element tablicy charc */
        fprintf(dataFile,"%s\n",charc);                                 /** Zapisanie do pliku linijki z polem streetName pierwszego elementu listy */
        puts("Write street number:");                                   /** Wyswietlenie komunikatu funkcja puts */
        scanf("%d",&num);                                               /** Pobranie od uzytkownika liczby i zapisanie jej do zmiennej num*/
        (*head)->streetNumber=num;                                      /** Przypisanie polu streetName wartosci zmiennej num */
        fprintf(dataFile,"%d\n",num);                                   /** Zapisanie do pliku linijki z polem streetNumber pierwszego elementu listy */
        puts("Write postcode:");                                        /** Wyswietlenie komunikatu funkcja puts */
        scanf("%d",&num);                                               /** Pobranie od uzytkownika liczby i zapisanie jej do zmiennej num*/
        (*head)->postcode=num;                                          /** Przypisanie polu postcode wartosci zmiennej num */
        puts("Write city:");                                            /** Wyswietlenie komunikatu funkcja puts */
        scanf("%s",&charc);                                             /** Pobranie od uzytkownika ciagu znakow i zapisanie go do zmiennej charc*/
        for(int i=0; i<50; i++)                                         /** Petla for wykonujaca sie 50 razy */
            (*head)->city[i]=charc[i];                                  /** Przypisanie polu city pierwszego elementu listy wartosci zmiennej num */
        fprintf(dataFile,"%s\n",charc);                                 /** Zapisanie do pliku linijki z polem city pierwszego elementu listy */
        puts("Write phone number:");                                    /** Wyswietlenie komunikatu funkcja puts */
        scanf("%d",&num);                                               /** Pobranie od uzytkownika liczby i zapisanie jej do zmiennej num*/
        fprintf(dataFile,"%d",num);                                     /** Zapisanie do pliku linijki z polem phoneNumber pierwszego elementu listy */
        (*head)->phoneNumber=num;                                       /** Przypisanie polu phoneNumber wartosci zmiennej num */
   		(*head)->prev = NULL;                                           /** Wzkaznikowi na element poprzedni i nastepny aktualnego elementu listy zostaje przypisana wartosc aktualego elementu listy */
    	(*head)->next = NULL;                                           /** Wzkaznikowi na element nastepny nastepnego elementu aktualnego listy zostaje przypisana wartosfc NULL */
	} else {                                                            /** Przejscie do alternatywnych intrukcji w przypadku niespelnienia warunku */
            listElement *curr=*head;                                    /** Deklaracja wzkaznika na element aktualny listy i prypisanie mu wartosci wzkaznika na pierwszy element listy  */
            listElement *newElement;
            while (curr->next != NULL) {                                /** Petla while dzialajaca do momentu az pole nastepne w aktualnej strukturze bedzie rowne NULL */
                curr = curr->next;                                      /** Przypisanie aktualnemu elementowi listy wartosci pola nastepnego w aktualnym elemencie listy */
            }
            curr->next=(listElement *)malloc(sizeof(listElement));      /** Alokacja pamieci na pole nastepne w aktualnym elemenie listy */
            fprintf(dataFile,"\n");                                     /** Stworzenie w pliku nowej linijki */
            curr->next->iD=idn;                                         /** Przypisanie polu iD aktualnego elementu listy wartosci zmiennej idn */
            fprintf(dataFile,"%d\n",num);                               /** Zapisanie do pliku linijki z polem iD aktualnego elementu listy */
            puts("Write first name:");                                  /** Wyswietlenie komunikatu funkcja puts */
            scanf("%s",&charc);                                         /** Pobranie od uzytkownika ciagu znakow i zapisanie go do zmiennej charc*/
            for(int i=0; i<50; i++)                                     /** Petla for wykonujaca sie 50 razy */
                curr->next->firstName[i]=charc[i];                      /** Kazdemu elementowi tablicy firstName pola next aktualnego elementu listy przypisywany jest kolejny element tablicy charc */
            fprintf(dataFile,"%s\n",charc);                             /** Zapisanie do pliku linijki z polem firstName pola next aktualnego elementu listy */
            puts("Write last name:");                                   /** Wyswietlenie komunikatu funkcja puts */
            scanf("%s",&charc);                                         /** Pobranie od uzytkownika ciagu znakow i zapisanie go do zmiennej charc*/
            for(int i=0; i<50; i++)                                     /** Petla for wykonujaca sie 50 razy */
                curr->next->lastName[i]=charc[i];                       /** Kazdemu elementowi tablicy lastName pola next aktualnego elementu listy przypisywany jest kolejny element tablicy charc */
            fprintf(dataFile,"%s\n",charc);                             /** Zapisanie do pliku linijki z polem lastName pola next aktualnego elementu listy */
            puts("Write street name:");                                 /** Wyswietlenie komunikatu funkcja puts */
            scanf("%s",&charc);                                         /** Pobranie od uzytkownika ciagu znakow i zapisanie go do zmiennej charc*/
            for(int i=0; i<50; i++)                                     /** Petla for wykonujaca sie 50 razy */
                    curr->next->streetName[i]=charc[i];                 /** Kazdemu elementowi tablicy streetName pola next aktualnego elementu listy przypisywany jest kolejny element tablicy charc */
            fprintf(dataFile,"%s\n",charc);                             /** Zapisanie do pliku linijki z polem streetName pola next aktualnego elementu listy */
            puts("Write street number:");                               /** Wyswietlenie komunikatu funkcja puts */
            scanf("%d",&num);                                           /** Pobranie od uzytkownika liczby i zapisanie jej do zmiennej num*/
            curr->next->streetNumber=num;                               /** Przypisanie polu streetNumber pola next aktualnego elementu listy wartosci zmiennej num */
            fprintf(dataFile,"%d\n",num);                               /** Zapisanie do pliku linijki z polem pola next streetNumber aktualnego elementu listy */
            puts("Write postcode:");                                    /** Wyswietlenie komunikatu funkcja puts */
            scanf("%d",&num);                                           /** Pobranie od uzytkownika liczby i zapisanie jej do zmiennej num*/
            curr->next->postcode=num;                                   /** Przypisanie polu postcode pola next aktualnego elementu listy wartosci zmiennej num */
            fprintf(dataFile,"%d\n",num);                               /** Zapisanie do pliku linijki z polem postcode pola next aktualnego elementu listy */
            puts("Write city:");                                        /** Wyswietlenie komunikatu funkcja puts */
            scanf("%s",&charc);                                         /** Pobranie od uzytkownika ciagu znakow i zapisanie go do zmiennej charc*/
            for(int i=0; i<50; i++)                                     /** Petla for wykonujaca sie 50 razy */
                curr->next->city[i]=charc[i];                           /** Kazdemu elementowi tablicy city pola next aktualnego elementu listy przypisywany jest kolejny element tablicy charc */
            fprintf(dataFile,"%s\n",charc);                             /** Zapisanie do pliku linijki z polem city pola next aktualnego elementu listy */
            puts("Write phone number:");                                /** Wyswietlenie komunikatu funkcja puts */
            scanf("%d",&num);                                           /** Pobranie od uzytkownika liczby i zapisanie jej do zmiennej num*/
            curr->next->phoneNumber=num;                                /** Przypisanie polu phoneNumber pola next aktualnego elementu listy wartosci zmiennej num */
            fprintf(dataFile,"%d",num);                                 /** Zapisanie do pliku linijki z polem Number pola next aktualnego elementu listy */
            curr->next->prev=curr;                                      /** Wzkaznikowi na element poprzedni i nastepny aktualnego elementu listy zostaje przypisana wartosc aktualnego elementu listy */
            curr->next->next = NULL;                                    /** Wzkaznikowi na element nastepny nastepnego elementu aktualnego listy zostaje przypisana wartosc NULL */
	}
    return;                                                             /** Funkcja nic nie zwraca */
}
/**
*@brief Funkcja odpowiedzialna za usuwanie pierwszego elementu listy
*@param **head to podwojny wzkaznik na aktualnie ostatni element listy
**/
void popFront(listElement **head){              /** Deklaracja funkcji popFront przyjmujacej jako argument podwojny wzkaznik na pierwszy element listy*/
    if (*head!=NULL) {                          /** Warunek sprawdzajacy czy pierwszy element listy nierowna sie NULL */
    	if((*head)->next==NULL) {               /** Warunek sprawdzajacy czy pole nastepny w pierwszym elemecie listy jest rowne NULL */
    		*head=NULL;                         /** Przypisanie pierwszemu elementu listy wartosci NULL */
		} else {                                /** Alternatywna droga w przypadku nie spelnienia warunku */
			listElement *tmp;                   /** Deklaracja wzkaznika tmp typu struktury listElement */
			tmp=(*head)->next;                  /** Przypisanie wzkaznikowi tmp wartosci pola next pierwszego elementu listy */
   			free(*head);                        /** Uwalnianie miejsca w pamieci w ktorej znajdowal sie pierwszy element listy */
   			*head=tmp;                          /** Pierwszemu elementowi listy zostaje przypisana zawartosc zmiennej tmp */
   	 		(*head)->prev=NULL;                 /** Przypisanie polu prev pierwszemu elementu listy wartosci NULL */
		}
	}
    return;                                     /** Funkcja nic nie zwraca */
}
/**
*@brief Funkcja odpowiedzialna za usuwanie ostatniego elementu listy
*@param **head to podwojny wzkaznik na aktualnie ostatni element listy
**/
void popBack(listElement **head){               /** Deklaracja funkcji popBack przyjmujacej jako argument podwojny wzkaznik na pierwszy element listy*/
	if((*head)->next==NULL)                     /** Warunek sprawdzajacy czy wzkaznik next pierwszego elemetu listy rowna sie NULL */
	{
		*head=NULL;                             /** Pierwszemu elementowi listy zostaje przypisana wartosc NULL */
	}else                                       /** Alternatywna droga w przypadku nie spelnienia warunku */
	{
		listElement *curr=*head;                /** Deklaracja wzkaznika na element aktualny listy i prypisanie mu wartosci wzkaznika na pierwszy element listy  */
		while (curr->next->next!= NULL) {       /** Petla while dzialajaca do momentu az pole nastepne w polu nastepnym w aktualnej strukturze bedzie rozne od NULL */
        curr = curr->next;                      /** Przypisanie aktualnemu elementowi listy wartosci pola nastepnego w aktualnym elemencie listy */
    	}
   		 free(curr->next);                      /** Uwalnianie miejsca w pamieci w ktorej znajdowal sie element nastepny pierszego elementu listy */
   		 curr->next=NULL;                       /** Przypisanie polu next aktualnego elementu listy wartosci NULL */
	}
    return;                                     /** Funkcja nic nie zwraca */
}
/**
*@brief Funkcja odpowiedzialna za usuwanie elementu z listy po jego numerze id
*@param **head to podwojny wzkaznik na aktualnie ostatni element listy
*@param index to numer elementu jaki ma zostac usuniety z listy
**/
void popByIndex(listElement **head, int index){ /** Deklaracja funkcji popByIndex przyjmujacej jako argumenty podwojny wzkaznik na pierwszy element listy oraz liczbe definiujaca index elementu jaki ma zostac usuniety z listy*/
    if(index==0)                                /** Warunek sprawdzajacy czy zmienna index rowna sie 0 */
        popFront(head);                         /** Wywolanie funkcji popFront z pierwszym elementem listy jako parametr */
    else{                                       /** Alternatywna droga w przypadku nie spelnienia warunku */
        listElement *curr=*head;                /** Deklaracja wzkaznika na element aktualny listy i prypisanie mu wartosci wzkaznika na pierwszy element listy  */
        listElement *tmp;                       /** Deklaracja wzkaznika tmp typu struktury listElement */
        while (curr->next != NULL && curr->iD<index) {/** Petla while dzialajaca do momentu az pole nastepne w polu nastepnym w aktualnej strukturze bedzie rozne od NULL oraz pole id w aktualnej strukturze bedzie mniejsze od wartosci zmiennej index */
            curr=curr->next;                    /** Przypisanie aktualnemu elementu listy wartosci pola next aktualnego elementu listy */
        }
        tmp = curr->next;                       /** Przypisanie wzkaznikowi tmp wartosci pola nastepnego aktualnego elementu listy */
        curr->next = tmp->next;                 /** Przypisanie polu next aktualnego elementu listy wartosci pola nastepnego we wzkazniku tmp */
        curr->next->prev=curr;                  /** Przypisanie polom next i prev aktualnego elementu listy wartosci aktulanego elementu listy */
        free(tmp);                              /** Uwalnianie miejsca w pamieci w ktorej znajdowal wzkaznik tmp */
    }
	return;
}
/**
*@brief Funkcja odpowiedzialna za wyswietlenie listy
*@param *head to wzkaznik na aktualnie ostatni element listy
**/
void showDatabase(listElement *head){           /** Deklaracja funkcji showDatabase przyjmujacej jako argument wzkaznik na pierwszy element listy */
    if(head==NULL)                              /** Warunek sprawdzajacy czy pierwszy element listy rowna sie NULL */
        puts("List is null");                   /** Wyswietlenie komunikatu ze lista jest pusta */
    else{                                       /** Alternatywna droga w przypadku nie spelnienia warunku */
        listElement *curr=head;                 /** Deklaracja wzkaznika na element aktualny listy i prypisanie mu wartosci wzkaznika na pierwszy element listy  */
        puts("ID  First Name Last Name          Street Name Street Num   Postcode            City  Phone Num");/** Wyswietlenie naglowka lista */
        do { /** Rozpoczenie petli do while */
            printf("%2d %10s %10s %20s %10d %10d %15s %10llu \n", curr->iD,curr->firstName, curr->lastName, curr->streetName, curr->streetNumber, curr->postcode, curr->city, curr->phoneNumber);/** Wyswietlenie wszystkich elementow listy stanowiacych jeden wiersz w bazie danych */
            curr=curr->next;                    /** Przypisanie aktualnemu elementowi listy wartosci pola next w aktualnym elemencie listy */
        }while (curr!=NULL);                    /** Petla do while dzialajaca do momentu az aktualny element listy bedzie rowny NULL */
    }
    return;                                     /** Funkcja nic nie zwraca */
}
/**
*@brief Funkcja odpowiedzialna za wyswietlenie elementow listy na ekranie w odwrotnej kolejnosci
*@param *head wzkaznik na aktualnie ostatni element listy
**/
void showDatabaseReverse(listElement *head){     /** Deklaracja funkcji showDatabaseReverse przyjmujacej jako argument wzkaznik na pierwszy element listy */
    if(head==NULL)                               /** Warunek sprawdzajacy czy pierwszy element listy rowna sie NULL */
        puts("List is null");                    /** Wyswietlenie komunikatu ze lista jest pusta */
    else                                         /** Alternatywna droga w przypadku nie spelnienia warunku */
    {
        puts("ID  First Name Last Name          Street Name Street Num   Postcode            City  Phone Num");/** Wyswietlenie naglowka lista */
        listElement *curr=head;                  /** Deklaracja wzkaznika na element aktualny listy i prypisanie mu wartosci wzkaznika na pierwszy element listy  */
        while (curr->next != NULL) {             /** Petla while dzialajaca do momentu pole nastepne w aktualnym elemencie listy bedzie rowne wartosci NULL */
            curr=curr->next;                     /** Przypisanie aktualnemu elementowi listy wartosci pola nastepne w aktualnym elmemencie listy */
        }
        do {                                     /** Rozpoczenie petli do while */
        	printf("%2d %10s %10s %20s %10d %10d %15s %10llu \n", curr->iD,curr->firstName, curr->lastName, curr->streetName, curr->streetNumber, curr->postcode, curr->city, curr->phoneNumber);/** Wyswietlenie wszystkich elementow listy stanowiacych jeden wiersz w bazie danych */
            curr=curr->prev;                     /** Przypisanie aktualnemu elementowi listy wartosci pola porpzedni w aktualnym elemencie listy */
		}while(curr!=NULL);                      /** Petla do while dzialajaca do momentu az aktualny element listy bedzie rowny NULL */
    }
    return;                                      /** Funkcja nic nie zwraca */
}
/**
*@brief Funkcja odpowiedzialna za pokazanie odpowiedniej wiersza w liscie i jego wyswietlenie w zaleznosci
* od wybranego parametru wyszukiwania
*@param *head to wzkaznik na aktualnie ostastni element listy
*@param *iD2 to numer id po jakim uzytkownik chce wyszukac dane w liscie
*@param *firstName2 to tablica zawierajaca imie po jakim chcemy wyszukac dane w liscie
*@param *lastName2 to tablica zawierajaca nazwisko po jakim chcemy wyszukac dane w liscie
*@param *streetName2 to tablica zawierajaca ulice po jakim chcemy wyszukac dane w liscie
*@param *streetNumber2 to numer domu po jakim chcemy wyszukac dane w liscie
*@param *postcode2 to numer kodu pocztowego po jakim chcemy wyszukac dane w liscie
*@param *city to tablica zawierajaca nazwe miasta po jakim chcemy wyszukac dane w liscie
*@param *phonenumber to numer telefonu po jakim chcemy wyszukac dane w liscie
**/
void searchInDatabase(listElement *head, int iD2, char firstName2[50], char lastName2[50], char streetName2[50], int streetNumber2, int postcode2, char city2[50], unsigned long long int phoneNumber2){/** Deklaracja funkcji searchInDatabase*/
    if(head==NULL)                              /** Warunek sprawdzajacy czy pierwszy element listy rowna sie NULL */
        puts("List is null");                   /** Wyswietlenie komunikatu ze lista jest pusta */
    else{                                       /** Alternatywna droga w przypadku nie spelnienia warunku */
        listElement *curr=head;                 /** Deklaracja wzkaznika na element aktualny listy i prypisanie mu wartosci wzkaznika na pierwszy element listy  */
        do {                                    /** Rozpoczenie petli do while */
            if(curr->iD==iD2)                   /** Warunek sprawdzajacy czy pole iD w aktualnym elemencie listy jest rowne zmiennej iD2*/
                printf("%2d %10s %10s %20s %10d %10d %15s %10llu \n", curr->iD,curr->firstName, curr->lastName, curr->streetName, curr->streetNumber, curr->postcode, curr->city, curr->phoneNumber);/** Wyswietlenie wszystkich elementow listy stanowiacych jeden wiersz w bazie danych */
            if(strcmp(curr->firstName,firstName2)==0)                   /** Warunek sprawdzajacy czy pole firstName w aktualnym elemencie listy jest rowne zmiennej firstName2*/
                printf("%2d %10s %10s %20s %10d %10d %15s %10llu \n", curr->iD,curr->firstName, curr->lastName, curr->streetName, curr->streetNumber, curr->postcode, curr->city, curr->phoneNumber);/** Wyswietlenie wszystkich elementow listy stanowiacych jeden wiersz w bazie danych */
            if(strcmp(curr->lastName,lastName2)==0)                     /** Warunek sprawdzajacy czy pole lastName w aktualnym elemencie listy jest rowne zmiennej lastName2*/
                printf("%2d %10s %10s %20s %10d %10d %15s %10llu \n", curr->iD,curr->firstName, curr->lastName, curr->streetName, curr->streetNumber, curr->postcode, curr->city, curr->phoneNumber);/** Wyswietlenie wszystkich elementow listy stanowiacych jeden wiersz w bazie danych */
            if(strcmp(curr->streetName,streetName2)==0)                 /** Warunek sprawdzajacy czy pole iD w aktualnym elemencie listy jest rowne zmiennej streetName2*/
                printf("%2d %10s %10s %20s %10d %10d %15s %10llu \n", curr->iD,curr->firstName, curr->lastName, curr->streetName, curr->streetNumber, curr->postcode, curr->city, curr->phoneNumber);/** Wyswietlenie wszystkich elementow listy stanowiacych jeden wiersz w bazie danych */
            if(curr->streetNumber==streetNumber2)                       /** Warunek sprawdzajacy czy pole streetNumber w aktualnym elemencie listy jest rowne zmiennej streetNumber2*/
                printf("%2d %10s %10s %20s %10d %10d %15s %10llu \n", curr->iD,curr->firstName, curr->lastName, curr->streetName, curr->streetNumber, curr->postcode, curr->city, curr->phoneNumber);/** Wyswietlenie wszystkich elementow listy stanowiacych jeden wiersz w bazie danych */
            if(curr->postcode==postcode2)                               /** Warunek sprawdzajacy czy pole postcode w aktualnym elemencie listy jest rowne zmiennej postcode*/
                printf("%2d %10s %10s %20s %10d %10d %15s %10llu \n", curr->iD,curr->firstName, curr->lastName, curr->streetName, curr->streetNumber, curr->postcode, curr->city, curr->phoneNumber);/** Wyswietlenie wszystkich elementow listy stanowiacych jeden wiersz w bazie danych */
            if(strcmp(curr->city,city2)==0)                             /** Warunek sprawdzajacy czy pole city w aktualnym elemencie listy jest rowne zmiennej city2*/
                printf("%2d %10s %10s %20s %10d %10d %15s %10llu \n", curr->iD,curr->firstName, curr->lastName, curr->streetName, curr->streetNumber, curr->postcode, curr->city, curr->phoneNumber);/** Wyswietlenie wszystkich elementow listy stanowiacych jeden wiersz w bazie danych */
            if(curr->phoneNumber==phoneNumber2)                         /** Warunek sprawdzajacy czy pole phoneNumber w aktualnym elemencie listy jest rowne zmiennej phoneNumber2*/
                printf("%2d %10s %10s %20s %10d %10d %15s %10llu \n", curr->iD,curr->firstName, curr->lastName, curr->streetName, curr->streetNumber, curr->postcode, curr->city, curr->phoneNumber);/** Wyswietlenie wszystkich elementow listy stanowiacych jeden wiersz w bazie danych */
            curr=curr->next;                                            /** Przypisanie aktualnemu elementowi listy wartosci pola nastepne w aktualnym elmemencie listy */
        }while (curr!=NULL);                                            /** Petla do while dzialajaca do momentu az aktualny element listy bedzie rowny NULL */
    }
    return;                                                             /** Funkcja nic nie zwraca */
}
/**
*@brief Funkcja odpowiedzialna za edycje danych w liscie
*@param *head to wzkaznik na aktualnie ostastni element listy
*@param *iD2 to numer id po jakim uzytkownik chce wyszukac dane w liscie
**/
void editInDatabase(listElement *head, int iD2){                        /** Deklaracja funkcji editInDatabase przyjmujacej jako argument wzkaznik na pierwszy element listy oraz zmienna iD2 typu int*/
    int option4;
    if(head==NULL)                                                      /** Warunek sprawdzajacy czy pierwszy element listy rowna sie NULL */
        puts("List is null");                                           /** Wyswietlenie komunikatu ze lista jest pusta */
    else{                                                               /** Alternatywna droga w przypadku nie spelnienia warunku */
        listElement *curr=head;                                         /** Deklaracja wzkaznika na element aktualny listy i prypisanie mu wartosci wzkaznika na pierwszy element listy  */
        do {                                                            /** Rozpoczenie petli do while */
            if(curr->iD==iD2){                                          /** Warunek sprawdzajacy czy pole iD w aktualnym elemencie listy jest rowne zmiennej iD2*/
                puts("List before editing:");                           /** Wyswietlenie komunikatu funkcja puts */
                printf("%2d %10s %10s %20s %10d %10d %15s %10llu \n", curr->iD,curr->firstName, curr->lastName, curr->streetName, curr->streetNumber, curr->postcode, curr->city, curr->phoneNumber);/** Wyswietlenie wszystkich elementow listy stanowiacych jeden wiersz w bazie danych */
                puts("What you want to edit?");         /** Wyswietlenie komunikatu funkcja puts */
                puts("1 - edit in first name pole");    /** Wyswietlenie komunikatu funkcja puts */
                puts("2 - edit in last name pole");     /** Wyswietlenie komunikatu funkcja puts */
                puts("3 - edit in street name pole");   /** Wyswietlenie komunikatu funkcja puts */
                puts("4 - edit in street number pole"); /** Wyswietlenie komunikatu funkcja puts */
                puts("5 - edit in postcode pole");      /** Wyswietlenie komunikatu funkcja puts */
                puts("6 - edit in city pole");          /** Wyswietlenie komunikatu funkcja puts */
                puts("7 - edit in phone number pole");  /** Wyswietlenie komunikatu funkcja puts */
                scanf("%d", &option4);                  /** Pobranie od uzytkownika liczby typu int i zapisanie jej do zmiennej option4 */
                switch(option4){                        /** Instrukcja warunkowa switch */
                case 1:                                 /** Intrukcje dla 1 */
                    puts("Write first name:");          /** Wyswietlenie komunikatu funkcja puts */
                    scanf(" %s", &curr->firstName);     /** Pobranie od uzytkownika ciagu znakow i zapisanie go do pola firstName w aktualnym elemencie listy */
                    break;                              /** Koniec instrukcji dla 1 */
                case 2:                                 /** Instrukcje dla 2 */
                    puts("Write last name:");           /** Wyswietlenie komunikatu funkcja puts */
                    scanf(" %s", &curr->lastName);      /** Pobranie od uzytkownika ciagu znakow i zapisanie go do pola lastName w aktualnym elemencie listy */
                    break;                              /** Koniec instrukcji dla 2 */
                case 3:                                 /** Instrukcje dla 3 */
                    puts("Write street name:");         /** Wyswietlenie komunikatu funkcja puts */
                    scanf(" %[^\n]s", &curr->streetName);/** Pobranie od uzytkownika ciagu znakow i zapisanie go do pola streetName w aktualnym elemencie listy */
                    break;                              /** Koniec instrukcji dla 3 */
                case 4:                                 /** Instrukcje dla 4 */
                    puts("Write street number:");       /** Wyswietlenie komunikatu funkcja puts */
                    scanf("%d", &curr->streetNumber);   /** Pobranie od uzytkownika liczby typu int i zapisanie jej do pola streetNumber w aktualnym elemencie listy */
                    break;                              /** Koniec instrukcji dla 4 */
                case 5:                                 /** Instrukcje dla 5 */
                    puts("Write postcode:");            /** Wyswietlenie komunikatu funkcja puts */
                    scanf("%d", &curr->postcode);       /** Pobranie od uzytkownika liczby typu int i zapisanie jej do pola postcode w aktualnym elemencie listy */
                    break;                              /** Koniec instrukcji dla 5 */
                case 6:                                 /** Instrukcje dla 6 */
                    puts("Write city:");                /** Wyswietlenie komunikatu funkcja puts */
                    scanf(" %[^\n]s", &curr->city);     /** Pobranie od uzytkownika ciagu znakow i zapisanie go do pola city w aktualnym elemencie listy */
                    break;                              /** Koniec instrukcji dla 6 */
                case 7:                                 /** Instrukcje dla 7 */
                    puts("Write phone number:");        /** Wyswietlenie komunikatu funkcja puts */
                    scanf("%d", &curr->phoneNumber);    /** Pobranie od uzytkownika liczby typu int i zapisanie jej do pola phoneNumber w aktualnym elemencie listy */
                    break;                              /** Koniec instrukcji dla 7 */
                }
                system("cls");                          /** Wywolanie systemowego polecenia cls */
                puts("List after editing:");            /** Wyswietlenie komunikatu funkcja puts */
                printf("%2d %10s %10s %20s %10d %10d %15s %10llu \n", curr->iD,curr->firstName, curr->lastName, curr->streetName, curr->streetNumber, curr->postcode, curr->city, curr->phoneNumber);/** Wyswietlenie wszystkich elementow listy stanowiacych jeden wiersz w bazie danych */
            }
            curr=curr->next;                            /** Przypisanie aktualnemu elementowi listy wartosci pola nastepne w aktualnym elmemencie listy */
        }while (curr!=NULL);                            /** Petla do while dzialajaca do momentu az aktualny element listy bedzie rowny NULL */
    }
    return;                                             /** Funkcja nic nie zwraca */
}
/**
*@brief Funkcja odpowiedzialna za pobranie danych z listy i zapisaniu ich do pliku
*@param *dataFile to wzkaznik na plik, z ktorego beda pobierane dane do listy
*@param *head to wzkaznik na aktualnie ostatni element listy
**/
void saveDatabase(FILE *dataFile, listElement *head){   /** Deklaracja funkcji dataFromFile przyjmujacej jako argumenty wzkaznik na plik oraz podwojny wzkaznik typu struktury listElement */
    if(head==NULL)                                      /** Warunek sprawdzajacy czy pierwszy element listy rowna sie NULL */
        puts("List is null");                           /** Wyswietlenie komunikatu ze lista jest pusta */
    else{                                               /** Alternatywna droga w przypadku nie spelnienia warunku */
        listElement *curr=head;                         /** Deklaracja wzkaznika na element aktualny listy i prypisanie mu wartosci wzkaznika na pierwszy element listy  */
        do {                                            /** Rozpoczenie petli do while */
            fprintf(dataFile,"%d\n",curr->iD);          /** Zapisanie do pliku linijki z polem iD aktualnego elementu listy */
            fprintf(dataFile,"%s\n",curr->firstName);   /** Zapisanie do pliku linijki z polem firstName aktualnego elementu listy */
            fprintf(dataFile,"%s\n",curr->lastName);    /** Zapisanie do pliku linijki z polem lastName aktualnego elementu listy */
            fprintf(dataFile,"%s\n",curr->streetName);  /** Zapisanie do pliku linijki z polem streetName aktualnego elementu listy */
            fprintf(dataFile,"%d\n",curr->streetNumber);/** Zapisanie do pliku linijki z polem streetNumber aktualnego elementu listy */
            fprintf(dataFile,"%d\n",curr->postcode);    /** Zapisanie do pliku linijki z polem postcode aktualnego elementu listy */
            fprintf(dataFile,"%s\n",curr->city);        /** Zapisanie do pliku linijki z polem city aktualnego elementu listy */
            fprintf(dataFile,"%llu\n",curr->phoneNumber);/** Zapisanie do pliku linijki z polem phoneNumber aktualnego elementu listy */
            curr=curr->next;                            /** Przypisanie aktualnemu elementowi listy wartosci pola nastepne w aktualnym elmemencie listy */
        }while (curr!=NULL);                            /** Petla do while dzialajaca do momentu az aktualny element listy bedzie rowny NULL */
    }
    return;                                                 /** Funkcja nic nie zwraca */
}
/**
*@brief Funkcja odpowiedzialna za komunikacje uzytkownika z programem,
* wyswietlajaca menu, pozwalajaca na wybor wybranej opcji.
*@param *dataFile to wzkaznik na plik, z ktorego beda pobierane dane do listy
*@param *head to podwojny wzkaznik na aktualnie ostatni element listy
*@param j to liczba wszystkich wierszy w pliku
*@param idn to licznik do autonumerowania wartosci id w liscie
**/
void startMenu(FILE *dataFile,listElement *head, int j, int idn){/** Deklaracja funkcji startMenu przyjmujacej jako argumenty wzkaznik na plik, podwojny wzkaznik typu struktury listElement oraz liczby typu int j i idn */
    int option=1;
    int index=-1;
    int iD2=NULL;
    char firstName2[50]={NULL};
    char lastName2[50]={NULL};
    char streetName2[50]={NULL};
    int streetNumber2=NULL;
    int postcode2=NULL;
    char city2[50]={NULL};
    unsigned long long int phoneNumber2=NULL;
    while(option){                        /** Petla while dzialajaca do momentu az zmienna option rozna od wartosci NULL */
        system("cls");                    /** Wywolanie systemowego polecenia cls */
        puts("This is the phone book.");  /** Wyswietlenie komunikatu funkcja puts */
        puts("Choose any option: ");      /** Wyswietlenie komunikatu funkcja puts */
        puts("0 - Save and exit.");       /** Wyswietlenie komunikatu funkcja puts */
        puts("1 - Add a new line.");      /** Wyswietlenie komunikatu funkcja puts */
        puts("2 - Edit a line.");         /** Wyswietlenie komunikatu funkcja puts */
        puts("3 - Delete a line.");       /** Wyswietlenie komunikatu funkcja puts */
        puts("4 - Show the database.");   /** Wyswietlenie komunikatu funkcja puts */
        puts("5 - Search in the database.");/** Wyswietlenie komunikatu funkcja puts */
        puts("6 - Sort in the database.");/** Wyswietlenie komunikatu funkcja puts */
        scanf("%d", &option);             /** Pobranie od uzytkownika liczby i zapisanie jej do zmiennej option */
        switch (option){                    /** Instrukcja warunkowa switch */
        case 0:                             /** Intrukcje dla 0 */
            continue;                       /** Przejscie do kolejnej iteracji w petli */
            break;                          /** Koniec instrukcji dla 0 */
        case 1:                             /** Intrukcje dla 1 */
            system("cls");                  /** Wywolanie systemowego polecenia cls */
            dataFile=fopen("data.txt", "a");/** Powiazanie pliku data.txt w trybie dopisu ze zmienna strumieniowa dataFile */
            pushNew(&head, dataFile, idn);  /** Wywolanie funkcji pushNew */
            idn++;                          /** Zwiekszenie liczby idn o 1 */
            fclose(dataFile);               /** Zamkniecie pliku dataFile */
            break;                          /** Koniec instrukcji dla 1 */
         case 2:                            /** Intrukcje dla 2 */
            iD2=NULL;                       /** Przypisanie zmiennej iD2 wartosci NULL*/
            system("cls");                  /** Wywolanie systemowego polecenia cls */
            puts("Write ID of element, where you want to edit:");/** Wyswietlenie komunikatu funkcja puts */
            scanf("%d",&iD2);               /** Pobranie od uzytkownika liczby i zapisanie jej do zmiennej iD2 */
            system("cls");                  /** Wywolanie systemowego polecenia cls */
            editInDatabase(head,iD2);       /** Wywolanie funkcji editInDatabase */
            system("pause");                /** Wywolanie systemowego polecenia pause */
            break;                          /** Koniec instrukcji dla 2 */
        case 3:                             /** Intrukcje dla 3 */
            system("cls");                  /** Wywolanie systemowego polecenia cls */
            puts("Write ID of element, which you want to delete:");/** Wyswietlenie komunikatu funkcja puts */
            scanf("%d", &index);            /** Pobranie od uzytkownika liczby i zapisanie jej do zmiennej index */
            if(index>0&&index<=j){          /** Warunek sprawdzajacy czy zmienna index jest wieksza od 0 i zmiejsza badz rowna zmiennej j */
                if(index==j)                /** Warunek sprawdzajacy czy zmienna index rowna sie wartosci zmiennej j */
                    popBack(&head);         /** Wywolanie funkcji popBack */
                else{                       /** Alternatywna droga w przypadku nie spelnienia warunku */
                    index--;                /** Zmiejszenie wartosci zmiennej index o 1 */
                    popByIndex(&head, index);/** Wywolanie funkcji popByIndex */
                }
                puts("Operation completed, but program must be restart.");/** Wyswietlenie komunikatu funkcja puts */
                system("pause");            /** Wywolanie systemowego polecenia pause */
                option=0;                   /** Przypisanie zmiennej option wartosci 0*/
            }
            else{                               /** Alternatywna droga w przypadku nie spelnienia warunku */
                puts("Bad number. Try again."); /** Wyswietlenie komunikatu funkcja puts */
                system("pause");                /** Wywolanie systemowego polecenia pause */
            }
            break;                              /** Koniec instrukcji dla 3 */
        case 4:                                 /** Intrukcje dla 4 */
            system("cls");                      /** Wywolanie systemowego polecenia cls */
            showDatabase(head);                 /** Wywolanie funkcji showDatabase */
            system("pause");                    /** Wywolanie systemowego polecenia pause */
            break;                              /** Koniec instrukcji dla 4 */
        case 5:                                 /** Intrukcje dla 5 */
            iD2=NULL;                           /** Przypisanie zmiennej iD2 wartosci NULL */
            for(int i=0; i<50; i++)             /** Petla for wykonujaca sie 50 razy */
                firstName2[i]=NULL;             /** Kazdemu elementowi tablicy firstName2 przypisywana jest wartosc NULL */
            for(int i=0; i<50; i++)             /** Petla for wykonujaca sie 50 razy */
                lastName2[i]=NULL;              /** Kazdemu elementowi tablicy lastName2 przypisywana jest wartosc NULL */
            for(int i=0; i<50; i++)             /** Petla for wykonujaca sie 50 razy */
                streetName2[i]=NULL;            /** Kazdemu elementowi tablicy streetName2 przypisywana jest wartosc NULL */
            streetNumber2=NULL;                 /** Przypisanie zmiennej streetNumber2 wartosci NULL */
            postcode2=NULL;                     /** Przypisanie zmiennej postcode2 wartosci NULL */
            for(int i=0; i<50; i++)             /** Petla for wykonujaca sie 50 razy */
                city2[i]=NULL;                  /** Kazdemu elementowi tablicy city2 przypisywana jest wartosc NULL */
            phoneNumber2=NULL;                  /** Przypisanie zmiennej phoneNumber2 wartosci NULL */
            system("cls");                      /** Wywolanie systemowego polecenia cls */
            puts("Choose any option:");         /** Wyswietlenie komunikatu funkcja puts */
            puts("0 - Exit");                   /** Wyswietlenie komunikatu funkcja puts */
            puts("1 - search in ID pole");      /** Wyswietlenie komunikatu funkcja puts */
            puts("2 - search in first name pole");/** Wyswietlenie komunikatu funkcja puts */
            puts("3 - search in last name pole");/** Wyswietlenie komunikatu funkcja puts */
            puts("4 - search in street name pole");/** Wyswietlenie komunikatu funkcja puts */
            puts("5 - search in street number pole");/** Wyswietlenie komunikatu funkcja puts */
            puts("6 - search in postcode pole");/** Wyswietlenie komunikatu funkcja puts */
            puts("7 - search in city pole");        /** Wyswietlenie komunikatu funkcja puts */
            puts("8 - search in phone number pole");/** Wyswietlenie komunikatu funkcja puts */
            int option2=0;
            scanf("%d", &option2);                  /** Pobranie od uzytkownika liczby i zapisanie jej do zmiennej option2 */
            switch(option2){                        /** Instrukcja warunkowa switch */
            case 0:                                 /** Intrukcje dla 0 */
                continue;                           /** Przejscie do kolejnej iteracji w petli */
                break;                              /** Koniec instrukcji dla 0 */
            case 1:                                 /** Intrukcje dla 1 */
                system("cls");                      /** Wywolanie systemowego polecenia cls */
                puts("Write ID:");                  /** Wyswietlenie komunikatu funkcja puts */
                scanf("%d",&iD2);                   /** Pobranie od uzytkownika liczby i zapisanie jej do zmiennej iD2 */
                system("cls");                      /** Wywolanie systemowego polecenia cls */
                searchInDatabase(head, iD2, firstName2, lastName2, streetName2, streetNumber2, postcode2, city2, phoneNumber2);/** Wywolanie funkcji searchInDatabase */
                system("pause");                    /** Wywolanie systemowego polecenia pause */
                break;                              /** Koniec instrukcji dla 1 */
            case 2:                                 /** Intrukcje dla 2 */
                system("cls");                      /** Wywolanie systemowego polecenia cls */
                puts("Write first name:");          /** Wyswietlenie komunikatu funkcja puts */
                scanf("%s", &firstName2);           /** Pobranie od ciagu znakow i zapisanie go do zmiennej firstName2 */
                system("cls");                      /** Wywolanie systemowego polecenia cls */
                searchInDatabase(head, iD2, firstName2, lastName2, streetName2, streetNumber2, postcode2, city2, phoneNumber2);/** Wywolanie funkcji searchInDatabase */
                system("pause");                    /** Wywolanie systemowego polecenia pause */
                break;                              /** Koniec instrukcji dla 2 */
            case 3:                                 /** Intrukcje dla 3 */
                system("cls");                      /** Wywolanie systemowego polecenia cls */
                puts("Write last name:");           /** Wyswietlenie komunikatu funkcja puts */
                scanf("%s", &lastName2);            /** Pobranie od uzytkownika ciagu znakow i zapisanie go do zmiennej lastName2 */
                system("cls");                      /** Wywolanie systemowego polecenia cls */
                searchInDatabase(head, iD2, firstName2, lastName2, streetName2, streetNumber2, postcode2, city2, phoneNumber2);/** Wywolanie funkcji searchInDatabase */
                system("pause");                    /** Wywolanie systemowego polecenia pause */
                break;                              /** Koniec instrukcji dla 3 */
            case 4:                                 /** Intrukcje dla 4 */
                system("cls");                      /** Wywolanie systemowego polecenia cls */
                puts("Write street name:");         /** Wyswietlenie komunikatu funkcja puts */
                scanf(" %[^\n]s", &streetName2);    /** Pobranie od uzytkownika ciagu znakow i zapisanie go do zmiennej streetName2 */
                system("cls");                      /** Wywolanie systemowego polecenia cls */
                searchInDatabase(head, iD2, firstName2, lastName2, streetName2, streetNumber2, postcode2, city2, phoneNumber2);/** Wywolanie funkcji searchInDatabase */
                system("pause");                    /** Wywolanie systemowego polecenia pause */
                break;                              /** Koniec instrukcji dla 4 */
            case 5:                                 /** Intrukcje dla 5 */
                system("cls");                      /** Wywolanie systemowego polecenia cls */
                puts("Write street number:");       /** Wyswietlenie komunikatu funkcja puts */
                scanf("%d", &streetNumber2);        /** Pobranie od uzytkownika liczby i zapisanie jej do zmiennej streetNumber2 */
                system("cls");                      /** Wywolanie systemowego polecenia cls */
                searchInDatabase(head, iD2, firstName2, lastName2, streetName2, streetNumber2, postcode2, city2, phoneNumber2);/** Wywolanie funkcji searchInDatabase */
                system("pause");                    /** Wywolanie systemowego polecenia pause */
                break;                              /** Koniec instrukcji dla 5 */
            case 6:                                 /** Intrukcje dla 6 */
                system("cls");                      /** Wywolanie systemowego polecenia cls */
                puts("Write postcode:");            /** Wyswietlenie komunikatu funkcja puts */
                scanf("%d", &postcode2);            /** Pobranie od uzytkownika liczby i zapisanie jej do zmiennej postcode2*/
                system("cls");                      /** Wywolanie systemowego polecenia cls */
                searchInDatabase(head, iD2, firstName2, lastName2, streetName2, streetNumber2, postcode2, city2, phoneNumber2);/** Wywolanie funkcji searchInDatabase */
                system("pause");                    /** Wywolanie systemowego polecenia pause */
                break;                              /** Koniec instrukcji dla 6 */
            case 7:                                 /** Intrukcje dla 7 */
                system("cls");                      /** Wywolanie systemowego polecenia cls */
                puts("Write city:");                /** Wyswietlenie komunikatu funkcja puts */
                scanf(" %[^\n]s", &city2);          /** Pobranie od uzytkownika ciagu znakow i zapisanie go do zmiennej city2*/
                system("cls");                      /** Wywolanie systemowego polecenia cls */
                searchInDatabase(head, iD2, firstName2, lastName2, streetName2, streetNumber2, postcode2, city2, phoneNumber2);/** Wywolanie funkcji searchInDatabase */
                system("pause");                    /** Wywolanie systemowego polecenia pause */
                break;                              /** Koniec instrukcji dla 7 */
            case 8:                                 /** Intrukcje dla 8 */
                system("cls");                      /** Wywolanie systemowego polecenia cls */
                puts("Write phone number:");        /** Wyswietlenie komunikatu funkcja puts */
                scanf("%llu", &phoneNumber2);       /** Pobranie od uzytkownika liczby i zapisanie jej do zmiennej city2*/
                system("cls");                      /** Wywolanie systemowego polecenia cls */
                searchInDatabase(head, iD2, firstName2, lastName2, streetName2, streetNumber2, postcode2, city2, phoneNumber2);/** Wywolanie funkcji searchInDatabase */
                system("pause");                    /** Wywolanie systemowego polecenia pause */
                break;                              /** Koniec instrukcji dla 8 */
            }
            break;                                  /** Koniec instrukcji dla 5 */
        case 6:                                     /** Intrukcje dla 6 */
            system("cls");                          /** Wywolanie systemowego polecenia cls */
            puts("Choose any option:");             /** Wyswietlenie komunikatu funkcja puts */
            puts("0 - Exit");                       /** Wyswietlenie komunikatu funkcja puts */
            puts("1 - sort by ID ascending");       /** Wyswietlenie komunikatu funkcja puts */
            puts("2 - sort by ID descending");      /** Wyswietlenie komunikatu funkcja puts */
            int option3=0;
            scanf("%d",&option3);                   /** Pobranie od uzytkownika liczby i zapisanie jej do zmiennej option3 */
            switch(option3){                        /** Instrukcja warunkowa switch */
            case 0:                                 /** Intrukcje dla 0 */
                continue;                           /** Przejscie do kolejnej iteracji w petli */
                break;                              /** Koniec instrukcji dla 0 */
            case 1:                                 /** Intrukcje dla 1 */
                system("cls");                      /** Wywolanie systemowego polecenia cls */
                showDatabase(head);                 /** Wywolanie funkcji showDatabase */
                system("pause");                    /** Wywolanie systemowego polecenia pause */
                break;                              /** Koniec instrukcji dla 1 */
            case 2:                                 /** Intrukcje dla 2 */
                system("cls");                      /** Wywolanie systemowego polecenia cls */
                showDatabaseReverse(head);          /** Wywolanie funkcji showDatabaseReverse */
                system("pause");                    /** Wywolanie systemowego polecenia pause */
                break;                              /** Koniec instrukcji dla 2 */
            }
            break;                                  /** Koniec instrukcji dla 6 */
        default:                                    /** Intrukcje domyslne */
            puts(" ");                              /** Wyswietlenie komunikatu funkcja puts */
            break;                                  /** Koniec instrukcji domyslnych */
        }
    }
    return;                                         /** Funkcja nic nie zwraca */
}
/**
*@brief Glowna funcja programu.
*Nastepuje w niej deklaracja pierwszego elementu listy.
*Tworzy powiazanie z plikiem
*Zlicza liczbe wierszy w pliku
*Wywoluje funkcje zapisu do listy, wyswietla menu, zapisuje plik
**/
int main()
{
    FILE *dataFile;
    listElement *head;
    head=(listElement*)malloc(sizeof(listElement));             /** Alokacja pamięci z wykorzystaniem funkcji malloc dla wzkaznika head */
    head=NULL;                                                  /** Przypisanie wkzaznikowi head wartosci NULL */
    dataFile=fopen("data.txt", "r");                            /** Powiazanie pliku data.txt w trybie odczytu ze zmienna strumieniowa dataFile */
    char charc[50];
    int j=0, idn=1;
    while((fgets(charc, sizeof(charc), dataFile)) != NULL) {     /** Pętla while dzialajaca do momentu az funkcja fgets zwroci wartosc NULL */
        j++;                                                     /** Zwiekszenie wartosci zmiennej j o 1*/
    }
    j=j/8;                                                       /** Przypisanie zmiennej j wartosci zmiennej j podzielonej przez 8 */
    fclose(dataFile);                                            /** Zamkniecie pliku dataFile */
    dataFile=fopen("data.txt", "r");                             /** Powiazanie pliku data.txt w trybie odczytu ze zmienna strumieniowa dataFile */
    for(int i=0; i<j; i++){                                      /** Petla for dzialajca tyle razy ile wynosi wartosc zmiennej j */
        dataFromFile(dataFile, &head, idn);                      /** Wywolanie funkcji dataFromFile */
        idn++;                                                   /** Zwiekszenie wartosci zmiennej idn o 1*/
    }
    fclose(dataFile);                                           /** Zamkniecie pliku dataFile */
    startMenu(dataFile, head, j, idn);                          /** Wywolanie funkcji startMenu */
    dataFile=fopen("data.txt", "w");                            /** Powiazanie pliku data.txt w trybie zapisu ze zmienna strumieniowa dataFile */
    saveDatabase(dataFile, head);                               /** Wywolanie funkcji saveDatabase */
    fclose(dataFile);                                           /** Zamkniecie pliku dataFile */
    return 0;                                                   /** Zwrocenie wartosci 0 */
}
/*
Ksiazka telefoniczna – Dodawanie/usuwanie/edycja ksiazki telefonicznej (ID, nazwisko,
imie, adres(ulica, nr domu/mieszkania, kod pocztowy, miasto), telefon). Wyœwietlanie
kontaktów ksiazki telefonicznej z mozliwoœcii sortowania rosnacego/malejacego.
Wyszukiwanie kontaktów. Zapisywanie/wczytywanie kontaktów do/z pliku.
Wykorzystanie list
*/
