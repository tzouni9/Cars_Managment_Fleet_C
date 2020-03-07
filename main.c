#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<windows.h>

void printMainMenu();
void newInput(int numOfSigns);
void deleteSign(int numOfSigns);
void search(int numOfSigns);
void replace(int numOfSigns);
void printReplaceLabel(int numOfSigns);

	FILE *file;
	int c, stock,numOfSigns,inputError,minYear = 2000,maxYear=2020,colorLines=0,brandLines=0;
 	char buffer[200],item[10],line[2048];
	
	char menuInput[100],preCheck[100],brand[100],loadedBrand[100],color[100];
	int i,num, plate,numPossible,year;
	bool state = false;
	
int main() {
	
	SetConsoleOutputCP(1253);			//GREEK SUPPORT
	system("color a");					//GREEN COLOR

	file = fopen("dataSigns.bin", "rb");		//HERE WE READ THE NUMBER OF SIGNS FROM BIN FILE, THIS NUMBER WILL + OR - IF ADD OR DELETE A ITEM
	fread(&numOfSigns, sizeof(int), 1, file);  	
  	fclose(file);
  	
  	file = fopen("colors.txt","r");
  	while (fgets(line, sizeof(line), file)) {
        colorLines++;	
   		}
    fclose(file);
    
	file = fopen("brands.txt","r");
  	while (fgets(line, sizeof(line), file)) {
        brandLines++;	
   		}
    fclose(file);
	
	printMainMenu();		
	do {
		num = 0;
		printf("\n\t\t\tйамте лиа епикоцг :  ");
		fgets(menuInput,100,stdin);				//GET INPUT AND SCAN IT FOR INT, IF IT ISN'T INT  AND IF IT ISN'T 1,2,3,4,5,8,9 THEN DEAFUALT RUNS
		sscanf(menuInput, "%d", &num);
	      switch (num) {
        case 1:									//OPEN THE SIGNS.TXT AND PRINT IT
			system("cls"); printf("\n_______________________________________________________________________\n");
			printf("\n\t\t\t    елжамисг окым");
			printf("\n_______________________________________________________________________\n"); 
			printf("\n\tпимайида\tлаяйа\t\tвяыла\t\tетос");
			printf("\n_______________________________________________________________________\n\n"); 
        	file = fopen("Signs.txt", "r");										
			while (fgets(line, sizeof(line), file)) {
        		printf("\t%s", line);
    		}
    		printf("\n\nбяехгйам %d еццяажес",numOfSigns);
    		fclose(file);
    		printf("\n\n\twhen you're ready ");system("pause"); system("cls"); printMainMenu();
          break;
        case 2: system("cls");  newInput(numOfSigns); 			// ADD A SIGN
          break;
        case 3: system("cls"); deleteSign(numOfSigns);			//REMOVE A SIGN
          break;
        case 4: replace(numOfSigns);							//REPLACE A SIGN
         break;
        case 5: search(numOfSigns);  							//SEARCH FRO A SIGN
         break;
        case 8 : printMainMenu();
         break;
        case 9 : exit(0);
          break;
        default:
        	system("cls");
          	printf("\n\n\t\t г епикоцг дем упаявеи сто лемоу ╧ кахос INPUT ! \t *** деите то лемоу еисацымтас 8\n");
          break;
 	      }
	}while(true);
	return 0;
}


void printMainMenu(){
	//prints the main menu
	system("cls");
	printf("\n\t\t\tCAR MANAGMENT V 1.0  2019\n\n");
	printf("\n_______________________________________________________________________\n");
	printf("\n\t\t\t\tMAIN MENU");
	printf("\n_______________________________________________________________________\n\n");
	printf("\t\t\t 1.   елжамисг окым\n\t\t\t 2.   еисацыцг меас еццяажгс\n\t\t\t 3.   диацяажг еццяажгс\n\t\t\t 4.   амамеысг еццяажгс\n\t\t\t 5.   амафгтгсг\n\t\t\t 9.   QUIT\n");
}

void printNewInputLabel(int phase){
	//prints input label
		printf("\n\t\t*** еисацыцг меас еццяажгс *** ");
		printf("\n_______________________________________________________________________\n");
		printf("\n\t\t 0.   епистяоцг сто аявийо лемоу");
		if(phase == 2){
			printf("\n\t\t 1.   диахесглес лаяйес аутойимгтым");
		}
		if(phase == 1){
			printf("\n\t\t 1.   деите тис йатавыяилемес пимайидес");
		}
		if(phase == 3){
			printf("\n\t\t 1.   деите та диахесгла вяылата");
		}
		if(phase == 4){
			printf("\n\t\t **   апо 2000 еыс 2020");
		}
		if(phase == 0){
			printf(" выяис апохгйеусг");
			printf("\n\t\t 1.   епистяоцг сто аявийо лемоу ле апохгйеусг");
			printf("\n\t\t 2.   меа еццяажг выяис апохгйеусг");
			printf("\n\t\t 3.   меа еццяажг ле апохгйеусг");
		}
		printf("\n_______________________________________________________________________\n");
}

void printReplaceLabel(int phase){
	//prints input label
		printf("\n\t\t\tамамеыс еццяажгс");
		printf("\n_______________________________________________________________________\n");
		printf("\n\t\t 0.   епистяоцг сто аявийо лемоу");
		if(phase == 2){
			printf("\n\t\t 1.   диахесглжс лаяйес аутойимгтым");
		}
		if(phase == 1){
			printf("\n\t\t 1.   деите тис йатавыяилемес пимайидес");
		}
		if(phase == 3){
			printf("\n\t\t 1.   деите та диахесгла вяылата");
		}
		if(phase == 4){
			printf("\n\t\t **   апо 2000 еыс 2020");
		}
		if(phase == 0){
			printf(" выяис апохгйеусг");
			printf("\n\t\t 1.   епистяоцг сто аявийо лемоу ле апохгйеусг");
			printf("\n\t\t 2.   меа амтийатастасг выяис апохгйеусг");
			printf("\n\t\t 3.   меа амтийатастасг апохгйеусг");
		}
		printf("\n_______________________________________________________________________\n");
}

void newInput(int numOfSigns){
	int platesArray[numOfSigns];			//LOAD THE PLATES
	file = fopen("Signs.txt", "r");
	i=0;
   	while (fgets(line, sizeof(line), file)) {
		sscanf(line, "%d", &platesArray[i]);
		i++;
	}	
	fclose(file);
	do {							//USER INPUT A NUMBER , IT WILL BE THE PLATE NUMBER OF NEW SIGN
		plate = -1;
		printNewInputLabel(1);
		printf("\n\n\tеисацете пимайида , ломо аяихлитийо леяос апо 1000 еыс 9999  : ");	
		fgets(preCheck,100,stdin);
		sscanf(preCheck, "%d", &plate); 			// AGAIN CHECK IF THE USER'S INPUT IS INT AND THEN IF THIS INT IS IN OF THE RANGE AND IF ALREADY PLATE EXISTS
		if(plate >= 1000 && plate <=9999){
			for (i = 0; i <= numOfSigns; i++){
				if(plate == platesArray[i]){
					system("cls");
					printf("\n\t\t   г пимайида упаявеи гдг ! \n\n\t\t");
					system("pause"); system("cls");
					state = false;
					break;
				}else{
					state = true;
				}
   			}
		}else if(plate == 0){					//OPTIONS FOR THE USER.
			plate = -1;
			main();
		}else if (plate == 1){
			printf("\n\n");
			for (i = 0; i < numOfSigns; i++){
        		printf("%d\n",platesArray[i]);
    		}
    		printf("\n\tFound %d plates\n",i);
    		printf("\tWhen you're ready "); system("pause"); system("cls");
		}else{
			system("cls");printf("\n\t\t\tкахос INPUT !\n\n\t");system("pause");system("cls");
		}
	}while(state != true);
	system("cls");
	do{									//USER WILL INPUT THE BRAND OF CAR
		state = false;
		numPossible = -1; 				
		printNewInputLabel(2);
		printf("\n\tепитувглемг еисацыцг пимайидас %d ! ",plate);
		printf("\n\tеисацете лаяйа аутойимгтоу г лиа епикоцг апо то лемоу : ");
		fgets(brand,50,stdin);
		strtok(brand, "\n");						//FOR SOMEONE REASON THE INPUT OF USER IF IS A STRING, TAKES \n AT THE END. I REMOVE IT HERE BECAUSE FIAT != FIAT\n
		sscanf(brand,"%d %s",&numPossible,&brand);   // WITH THIS TECHNIQUE I CHECK IF USER INPUT AN INT OR A STRING.

		char brands[50][i];	
		file = fopen("brands.txt", "r");
		for(i = 1; i <= brandLines; i++){				//CHECK IF AVAILABLE BRANDS EQUALS WITH THE INPUT OF USER
			fscanf(file, "%s", brands[i]);
		}
		fclose(file);
		if(numPossible == 0){						//OPTIONS FOR THE USER.
			main();
		}else if(numPossible == 1){
			printf("\n");
			file = fopen("brands.txt", "r");
			while ((c = getc(file)) != EOF) 
   			printf("%c", c);
			printf("\n\t When you're ready ");	system("pause");	system("cls");
			fclose(file);
		}else{
			for(i = 1;i <= brandLines;i++){
				if(strcmp(brand,brands[i]) == 0){
					state = true;
					break;
				}
			}
			
			if(state == true){
				break;
			}else{
				system("cls");
				printf("\n\t\t\tкахос INPUT !\n\n\t");
				system("pause");
				system("cls");
				}
			}	
		}while(state != true);	
	do {									// HERE THE USER WILL INPUT THE COLOR OF NEW CAR, THE CODE WORKS WITH SAME FUNCTION WITH BRAND 
		numPossible = -1;
		state = false;
		system("cls");printNewInputLabel(3);
		printf("\n\tепитувглемг еисацыцг пимайидас %d ! ",plate);
		printf("\n\tепитувглемг еисацыцг лаяйас %s ! ",brand);
		printf("\n\tеисацете вяыла аутойимгтоу г лиа епикоцг апо то лемоу : ");
		fgets(color,50,stdin);
		strtok(color, "\n");
		sscanf(color,"%d %s",&numPossible,&color);
		i=0;	
		char colors[50][colorLines];	
		file = fopen("colors.txt", "r");
		for(i = 1; i <= colorLines; i++){
			fscanf(file, "%s", colors[i]);
		}
    	fclose(file); 	
		if(numPossible == 0){
			main();
		}else if(numPossible == 1){
			printf("\n");
			file = fopen("colors.txt", "r");
			while ((c = getc(file)) != EOF) /* read the rest of the file */
   			printf("%c", c);
			printf("\n\t When you're ready ");system("pause");
			fclose(file);
		}else{
			for(i = 1;i <= colorLines;i++){
				if(strcmp(color,colors[i]) == 0){
					state = true;
					break;
				}
			}
			if(state == true){
				break;
			}else{
				system("cls");printf("\n\t\t\tкахос INPUT !\n\n\t");system("pause");system("cls");
			}
		}		
	}while(state != true);
	do{								//INPUT OF CONSTRUCTION YEAR
		year = -1;
		state = false;
		system("cls");	printNewInputLabel(4);
		printf("\n\tепитувглемг еисацыцг пимайидас %d ! ",plate);
		printf("\n\tепитувглемг еисацыцг лаяйас %s ! ",brand);
		printf("\n\tепитувглемг еисацыцг вяылатос %s !",color);
		printf("\n\tеисацете вяомокоциа танимолгсгс : ");			
		fgets(preCheck,100,stdin);
		sscanf(preCheck, "%d", &year); 					//TAKE AN INT AND THEN CHECK IT WITH IN THE RANGE OF ACCEPTABLE YEARS 
		if(year >= minYear && year <= maxYear){
			state = true;
		}else if(year == 0){
			year = -1;
			main();
		}else{
			system("cls");printf("\n\t\t\tкахос INPUT !\n\n\t");system("pause");system("cls");
		}	
	}while(state != true);
	do{													//CONFIRM AND SAVE 
		numPossible = -1;
		system("cls");
		printNewInputLabel(0);
		printf("\n\n\t\t\t пяоеписйопгсг еццяажгс \n");
		printf("\n_______________________________________________________________________\n");
		printf("\n\tпимайида\tлаяйа\t\tвяыла\t\tетос");	
		printf("\n_______________________________________________________________________\n");
		if(strcmp(brand,"ALFA-ROMEO")==0){
			printf("\n\t%d\t\t%s\t%s\t\t%d",plate,brand,color,year);
		}else{
			printf("\n\t%d\t\t%s\t\t%s\t\t%d",plate,brand,color,year);
		}
		printf("\n\n\t йамте лиа епикоцг : ");
		fgets(preCheck,100,stdin);					
		sscanf(preCheck, "%d", &numPossible);
		if(numPossible == 0){
			main();
		}else if(numPossible == 2){
			system("cls");	newInput(numOfSigns);
		}else if(numPossible == 1 || numPossible == 3){						//HERE I PARSE THE WHOLE TEXT INTO A STRING AND THEN I JUST ADD THE NEW SIGN , THEN + THE NUMBER OF SIGNS
			
			char wholeText[2048]={0},platePre[10],yearPre[10];
			file = fopen("Signs.txt", "r");
			while (fgets(line, sizeof(line), file)) {
					strcat(wholeText,line);			
    		}    		
			fclose(file);			
			sprintf(platePre, "%d", plate);
			sprintf(yearPre, "%d", year);
			strcat(wholeText,"\n");
			strcat(wholeText,platePre); strcat(wholeText,"\t\t");
			strcat(wholeText,brand); 
			if(strcmp(brand,"ALFA-ROMEO")==0){
				strcat(wholeText,"\t");
			}else{
				strcat(wholeText,"\t\t");
			}	
			strcat(wholeText,color); strcat(wholeText,"\t\t");
			strcat(wholeText,yearPre);							
    		file = fopen("Signs.txt", "w");
    		fprintf(file,"%s",wholeText);
    		fclose(file);		
			numOfSigns++;	
			file = fopen("dataSigns.bin", "wb");
			fwrite((const void*) & numOfSigns,sizeof(int),1,file);	
 			fclose(file);		
			if(numPossible ==1){main();}
			if(numPossible ==3){system("cls");newInput(numOfSigns);}
		}else {
			system("cls");printf("\n\t\t\tкахос INPUT !\n\n\t");system("pause");system("cls");
		}	
	}while(true);
}
	
void deleteSign(int numOfSigns){
	int maxPlate = 999;
	int minPlate = 10000;
	int platesArray[numOfSigns];				//LOAD THE SIGNED PLATES
	file = fopen("Signs.txt", "r");
	i=0;
   	while (fgets(line, sizeof(line), file)) {
		sscanf(line, "%d", &platesArray[i]);
		maxPlate = (platesArray[i]>maxPlate)? platesArray[i]:maxPlate;
		minPlate = (platesArray[i]<minPlate)? platesArray[i]:minPlate;      //CHECK THE MAX AND MIN PLATES FOR PRINTING AND CHECKING
		i++;
	}	
	fclose(file);
	if(minPlate == 10000 && maxPlate == 999){								//IT'S A LITTLE TRICKY BUT IF DON'T HAVE SIGNS THE USER CAN'T DELETE THE NOTHONG SO IF HAVE 0 SIGNS THE MIN AND MAX PLATES REMAIN IN THESE NUMBERS
		system("cls"); printf("\n_______________________________________________________________________\n");
			printf("\n\t\t\t    диацяажг еццяажгс");
			printf("\n_______________________________________________________________________\n\n\n");
			printf("\t\t\tдем упаявеи типота циа ма диацяаьете !\n\n ");
			system("pause"); system("cls");
	}else{
		do{
			bool plateExist = false;
			plate = -1;
			system("cls"); printf("\n_______________________________________________________________________\n");
			printf("\n\t\t\t    диацяажг еццяажгс");
			printf("\n_______________________________________________________________________\n");
			printf("\n\t\t 0.   епистяоцг сто аявийо лемоу");
			printf("\n\t\t 1.   деите тис йатавыяилемес пимайидес");
			printf("\n_______________________________________________________________________\n");			
			printf("\n\n\tеисацете пимайида , ломо аяихлитийо леяос апо %d еыс %d  : ",minPlate,maxPlate);	
			fgets(preCheck,100,stdin);
			sscanf(preCheck, "%d", &plate);
			if(plate >= minPlate && plate <= maxPlate){
				for (i = 0; i <= numOfSigns; i++){	
					if(plate == platesArray[i]){
						plateExist = true;				
					}
   				}
   				if(plateExist){
   					int plateCheck;
   					system("cls"); printf("\n_______________________________________________________________________\n");
					printf("\n\t\t\t    диацяажг еццяажгс");
					printf("\n_______________________________________________________________________\n");
   					printf("\n\t\t 0.   епистяоцг сто аявийо лемоу выяис апохгйеусг");
   					printf("\n\t\t 1.   епистяоцг сто аявийо лемоу ле апохгйеусг");
					printf("\n\t\t 2.   меа диацяажг выяис апохгйеусг");
					printf("\n\t\t 3.   меа диацяажг апохгйеусг");printf("\n_______________________________________________________________________\n");		
   					file = fopen("Signs.txt", "r");	
								while (fgets(line, sizeof(line), file)) {
									sscanf(line, "%d", &plateCheck);									
									if(plate == plateCheck){	
										printf("\n\tто овгла ле та паяайаты стоивеиа евеи епикецеи циа диацяажг :\n\n\t%s",line);							//ALSO TRICKY, IF THE PLATE TO DELETE IS THE SAME WITH THE PLATE OF THE READING FROM SYS FILE THEN , IT SKIP IT AND THIS LINE DON'T ADD IT TO THE WHOLE TEXT
									}	
    							}
								fclose(file);
   					printf("\n_______________________________________________________________________\n");
   					printf("\n\n\t йамте лиа епикоцг : ");
							fgets(preCheck,100,stdin);
							sscanf(preCheck, "%d", &numPossible);
							if(numPossible == 0){
								main();
							}else if(numPossible == 2){
								system("cls");	deleteSign(numOfSigns);
							}else if(numPossible == 1 || numPossible == 3){								
								int plateCheck;
   								char wholeText[2048]={0},delCar[256]={0};
								file = fopen("Signs.txt", "r");	
								while (fgets(line, sizeof(line), file)) {
									sscanf(line, "%d", &plateCheck);									
									if(plate != plateCheck){								//ALSO TRICKY, IF THE PLATE TO DELETE IS THE SAME WITH THE PLATE OF THE READING FROM SYS FILE THEN , IT SKIP IT AND THIS LINE DON'T ADD IT TO THE WHOLE TEXT
										strcat(wholeText,line);
									}else{
    								strcpy(delCar,line);
									}	
    							}
								fclose(file);						
    							file = fopen("Signs.txt", "w");
    							fprintf(file,"%s",wholeText);
    							fclose(file);
    							numOfSigns--;	
								file = fopen("dataSigns.bin", "wb");						//HERE THE NUMBER OF SIGNS JIST -1
								fwrite((const void*) & numOfSigns,sizeof(int),1,file);	
 								fclose(file);
 								system("cls"); printf("\n_______________________________________________________________________\n");
								printf("\n\t\t\t    диацяажг еццяажгс");
								printf("\n_______________________________________________________________________\n");
								printf("\n\t\t то алани ле стоивеиа :\n");
								printf("\n\t\t %s ",delCar);
								printf("\n\t\t диацяажгйе епитувыс !  ");
								system("pause");	
								if(numPossible ==3){system("cls");deleteSign(numOfSigns);}
							}else {
								system("cls");printf("\n\t\t\tкахос INPUT !\n\n\t");system("pause");system("cls");
							}								
				   }else{
				   		system("cls"); printf("\n_______________________________________________________________________\n");
						printf("\n\t\t\t    диацяажг еццяажгс");
						printf("\n_______________________________________________________________________\n");
				   		printf("\n\t\tг пимайида дем бяехгйе ! \n\n");
				   		system("pause"); system("cls");
				   }
			}else if(plate == 0){ 						//OPTIONS !
				plate = -1;
				main();
			}else if (plate == 1){
				printf("\n\n");
				for (i = 0; i <= numOfSigns; i++){
        			printf("%d\n",platesArray[i]);
    			}
    			printf("\n\tFound %d plates\n",i);
    			printf("\tWhen you're ready "); system("pause"); system("cls");
			}else{
				system("cls");printf("\n\t\t\tкахос INPUT !\n\n\t");system("pause");system("cls");
			}
		}while(true);
	}
}

void search(int numOfSigns){
	
	char bufferBrand[25] = {0},bufferColor[25]={0},preCheck[25] = {0};
	int bufferPlate,bufferYear,choice,maxPlate = 999,minPlate = 10000,searchPlate;
	
	char ArrBrands[25][numOfSigns],ArrColors[25][numOfSigns];
	int ArrPlates[numOfSigns],ArrYears[numOfSigns];
	
	file = fopen("Signs.txt", "r");							//READ AND SPLIT , IF YOU KNOW WHAT I MEAN !
	for(i=0;i<numOfSigns;i++){
		fscanf(file, "%d %s %s %d",&bufferPlate,bufferBrand,bufferColor,&bufferYear);
		strcpy(ArrBrands[i],bufferBrand);
		strcpy(ArrColors[i],bufferColor);
		ArrPlates[i] = bufferPlate;
		ArrYears[i] = bufferYear;
		maxPlate = (bufferPlate>maxPlate)? bufferPlate:maxPlate;
		minPlate = (bufferPlate<minPlate)? bufferPlate:minPlate; 
		}
	do{
		choice = -1;
		searchPlate = -1;
		system("cls"); printf("\n\t\t    *** амафгтгсг еццяажгс ***"); printf("\n_______________________________________________________________________\n");
		printf("\n\t\t 0.   епистяож9г сто аявийо лемоу");
		printf("\n\t\t 1.   амафгтгсг ле пимайида");
		printf("\n\t\t 2.   амафгтгсг ле лаяйа");
		printf("\n\t\t 3.   амафгтгсг ле вяыла");
		printf("\n\t\t 4.   амафгтгсг ле вяомокоциа");
		printf("\n_______________________________________________________________________\n");
		printf("\n\n\t\tйамте лиа епикоцг : ");	
		fgets(preCheck,100,stdin);
		sscanf(preCheck, "%d", &choice);
		switch(choice){														//ALSO WE CAN'T SEARCH FOR 0 SIGNS, SO AT EVERY CASE I CARE FOR THAT !
			case 0: main();													//CASE 0 = EXIT 	CASE 1 = SEARCH WITH PLATE 		CASE 2 = SEARCH WITH BRAND		CASE 3 = SEARCH WITH COLOR		CASE 4 = WITH YEAR
				break;
			case 1: system("cls"); printf("\n\t\t    *** амафгтгсгс ле пимайида ***"); printf("\n_______________________________________________________________________\n");
				if(minPlate == 10000 && maxPlate == 999){
					system("cls"); printf("\n_______________________________________________________________________\n");
					printf("\n\t\t\t    диацяажг еццяажгс");
					printf("\n_______________________________________________________________________\n\n\n");
					printf("\t\t\tдем упаявеи типота циа ма ьанете !\n\n ");
					system("pause"); system("cls");
				}else{
					do{	
						file = fopen("Signs.txt", "r");	
						searchPlate = -1;
						system("cls"); printf("\n\t\t    *** амафгтгсгс ле пимайида ***"); printf("\n_______________________________________________________________________\n");
						printf("\n\n\tеисацете пимайида , ломо аяихлитийо леяос апо %d еыс %d  : ",minPlate,maxPlate);
						fgets(preCheck,100,stdin);
						sscanf(preCheck, "%d", &searchPlate);									//TAKE AN INT AGAIN !
						if(searchPlate >= minPlate && searchPlate <= maxPlate){
							for (i = 0; i <= numOfSigns; i++){	
								fscanf(file, "%d %s %s %d",&bufferPlate,bufferBrand,bufferColor,&bufferYear);
								if(bufferPlate == searchPlate){									// IF USER HAVE BINGO WITH PLATE ,THEN THE SING WILL APPEAR
									do{
										choice = -1;
										system("cls");printf("\n\n\t\t\t*** то овгла бяехгйе ***");
										printf("\n_______________________________________________________________________\n\n");
										printf("\tпимайида\tлаяйа\t\tвяыла\t\tетос");	
										printf("\n_______________________________________________________________________\n");
										printf("\n\t%d\t\t%s\t\t%s\t\t%d\n",bufferPlate,bufferBrand,bufferColor,bufferYear);
										printf("\n_______________________________________________________________________\n\n");
										printf("\n\t\t 0.   епистяоцг сто аявийо лемоу");
										printf("\n\t\t 1.   меа амафгтгсг");
										printf("\n\n_______________________________________________________________________\n\n");
										printf("\n\n\t\t\t\tйамте лиа епикоцг : ");	
										fgets(preCheck,100,stdin);
										sscanf(preCheck, "%d", &choice);
										if(choice ==0){ main();
										}else if(choice == 1){search(numOfSigns);
										}else{
											system("cls");printf("\n\n\t\t\tкахос INPUT !\n\n "); system("pause");
										}
									}while(true);
								}
   							}
   						}else{
							system("cls");printf("\n\n\t\t\tкахос INPUT !\n\n "); system("pause");
						}
   						fclose(file);
					}while(true);
				}
				break;
			case 2: system("cls"); printf("\n\t\t    *** амафгтгсгс ле лаяйа ***"); printf("\n_______________________________________________________________________\n");
				if(minPlate == 10000 && maxPlate == 999){
					system("cls"); printf("\n_______________________________________________________________________\n");
					printf("\n\t\t\t    диацяажг еццяажгс");
					printf("\n_______________________________________________________________________\n\n\n");
					printf("\t\t\tдем упаявеи типота циа ма ьанете !\n\n ");
					system("pause"); system("cls");
				}else{
					do{
						state = false;
						numPossible = -1; //if brandNumPossible don't take input remain -1
							system("cls"); printf("\n\t\t    *** амафгтгсг ле лаяйа ***"); printf("\n_______________________________________________________________________\n\n");
							printf("\n\t\t 0.   епистяоцг сто аявийо лемоу");
							printf("\n\t\t 1.   деите тис лаяйес");
							printf("\n\n_______________________________________________________________________\n\n");
							printf("\n\tеисацете лаяйа аутойимгтоу г лиа епикоцг апо то лемоу : ");
							fgets(brand,50,stdin);
							strtok(brand, "\n");
							sscanf(brand,"%d %s",&numPossible,&brand);
							if(numPossible == 0){
								main();
							}else if(numPossible == 1){
								printf("\n");
								file = fopen("brands.txt", "r");
								while ((c = getc(file)) != EOF) /* read the rest of the file */
   								printf("%c", c);
								printf("\n\t When you're ready ");	system("pause");	system("cls");
								fclose(file);
							}else{
								file = fopen("brands.txt","r");
								for(i=0;i<brandLines;i++){
									fscanf(file,"%s",bufferBrand);
									if(strncmp(brand,bufferBrand,strlen(brand))==0){
										state = true;
									}
								}
								fclose(file);
								if(state == true){
									do{
										file = fopen("Signs.txt","r");
										system("cls");printf("\n\n\t\t\t*** ои еццяажес бяехгйам ***");printf("\n\n_______________________________________________________________________\n\n\n");
										printf("\tпимайида\tлаяйа\t\tвяыла\t\tетос");
										printf("\n_______________________________________________________________________\n\n");	
										for(i = 0;i < numOfSigns;i++){
											fscanf(file, "%d %s %s %d",&bufferPlate,bufferBrand,bufferColor,&bufferYear);
											if(strncmp(brand,bufferBrand,strlen(brand))==0){
												if(strcmp(bufferBrand,"ALFA-ROMEO")==0){
													printf("\t%d\t\t%s\t%s\t\t%d\n",bufferPlate,bufferBrand,bufferColor,bufferYear);
												}else{
													printf("\t%d\t\t%s\t\t%s\t\t%d\n",bufferPlate,bufferBrand,bufferColor,bufferYear);
												}	
											}
										}
											printf("\n_______________________________________________________________________\n\n");
											fclose(file);
											printf("\n\t\t 0.   епистяоцг сто аявийо лемоу");
											printf("\n\t\t 1.   меа амафгтгсг");
											printf("\n\n_______________________________________________________________________\n\n");
											printf("\n\n\t\t\tйамте лиа епикоцг : ");	
											fgets(preCheck,100,stdin);
											sscanf(preCheck, "%d", &choice);
											if(choice ==0){ main();
											}else if(choice == 1){search(numOfSigns);
											}else{
												system("cls");printf("\n\n\t\t\tкахос INPUT !\n\n "); system("pause");
											}
										}while(true);									
									}else{
										system("cls");
										printf("\n\t\t\tкахос INPUT !\n\n\t");
										system("pause");
										system("cls");
									}
								}	
						}while(state != true);	
					}
				break;
			case 3:	system("cls"); printf("\n\t\t    *** амафгтгсгс ле вяыла ***"); printf("\n_______________________________________________________________________\n");
				if(minPlate == 10000 && maxPlate == 999){
					system("cls"); printf("\n_______________________________________________________________________\n");
					printf("\n\t\t\t    диацяажг еццяажгс");
					printf("\n_______________________________________________________________________\n\n\n");
					printf("\t\t\tдем упаявеи типота циа ма ьанете !\n\n ");
					system("pause"); system("cls");
				}else{
					do{
						state = false;
						numPossible = -1; //if brandNumPossible don't take input remain -1
							system("cls"); printf("\n\t\t    *** амафгтгсг ле вяыла ***"); printf("\n_______________________________________________________________________\n\n");
							printf("\n\t\t 0.   епистяоцг сто аявийо лемоу");
							printf("\n\t\t 1.   деите та вяылата");
							printf("\n\n_______________________________________________________________________\n\n");
							printf("\n\tеисацете лаяйа аутойимгтоу г лиа епикоцг апо то лемоу : ");
							fgets(brand,50,stdin);
							strtok(brand, "\n");
							sscanf(brand,"%d %s",&numPossible,&brand);
							if(numPossible == 0){
								main();
							}else if(numPossible == 1){
								printf("\n");
								file = fopen("colors.txt", "r");
								while ((c = getc(file)) != EOF) /* read the rest of the file */
   								printf("%c", c);
								printf("\n\t When you're ready ");	system("pause");	system("cls");
								fclose(file);
							}else{
								file = fopen("colors.txt","r");
								for(i=0;i<colorLines;i++){
									fscanf(file,"%s",bufferColor);
									if(strncmp(brand,bufferColor,strlen(brand))==0){
										state = true;
									}
								}
								fclose(file);
								if(state == true){
									do{
										file = fopen("Signs.txt","r");
										system("cls");printf("\n\n\t\t\t*** ои еццяажес бяехгйам ***");printf("\n\n_______________________________________________________________________\n\n");
										printf("\tпимайида\tлаяйа\t\tвяыла\t\tетос");
										printf("\n_______________________________________________________________________\n\n\n");
										for(i = 0;i <= numOfSigns;i++){
											fscanf(file, "%d %s %s %d",&bufferPlate,bufferBrand,bufferColor,&bufferYear);
											if(strncmp(brand,bufferColor,strlen(brand))==0){
												if(strcmp(bufferBrand,"ALFA-ROMEO")==0){
													printf("\t%d\t\t%s\t%s\t\t%d\n",bufferPlate,bufferBrand,bufferColor,bufferYear);
												}else{
													printf("\t%d\t\t%s\t\t%s\t\t%d\n",bufferPlate,bufferBrand,bufferColor,bufferYear);
												}	
											}}
											printf("\n_______________________________________________________________________\n\n");
											fclose(file);
											printf("\n\t\t 0.   епистяоцг сто аявийо лемоу");
											printf("\n\t\t 1.   меа амафгтгсг");
											printf("\n\n_______________________________________________________________________\n\n");
											printf("\n\n\t\t\tйамте лиа епикоцг : ");	
											fgets(preCheck,100,stdin);
											sscanf(preCheck, "%d", &choice);
											if(choice ==0){ main();
											}else if(choice == 1){search(numOfSigns);
											}else{
												system("cls");printf("\n\n\t\t\tкахос INPUT !\n\n "); system("pause");
											}
										}while(true);									
									}else{
										system("cls");
										printf("\n\t\t\tкахос INPUT !\n\n\t");
										system("pause");
										system("cls");
									}
								}	
						}while(state != true);	
					}
				break;
			case 4:	system("cls"); printf("\n\t\t    *** амафгтгсг ле вяомокоциа ***"); printf("\n_______________________________________________________________________\n");
							if(minPlate == 10000 && maxPlate == 999){
					system("cls"); printf("\n_______________________________________________________________________\n");
					printf("\n\t\t\t    диацяажг еццяажгс");
					printf("\n_______________________________________________________________________\n\n\n");
					printf("\t\t\tдем упаявеи типота циа ма ьанете !\n\n ");
					system("pause"); system("cls");
				}else{
					do{
						state = false;
						numPossible = -1; //if brandNumPossible don't take input remain -1
						system("cls"); printf("\n\t\t    *** амафгтгсг ле вяомокоциа ***"); printf("\n_______________________________________________________________________\n\n");
						printf("\n\t\t 0.   епистяоцг сто аявийо лемоу");
						printf("\n\t\t **   апо 2000 еыс 2020");
						printf("\n\n_______________________________________________________________________\n\n");
						printf("\n\tеисацете вяомокоциа аутойимгтоу г лиа епикоцг апо то лемоу : ");
						fgets(brand,50,stdin);
						sscanf(brand,"%d",&numPossible);
						if(numPossible == 0){
							main();
						}else if(numPossible > minYear && numPossible <maxYear){
								do{
									file = fopen("Signs.txt","r");
									system("cls");printf("\n\n\t\t\t*** ои еццяажес бяехгйам ***");printf("\n\n_______________________________________________________________________\n\n");
									printf("\tпимайида\tлаяйа\t\tвяыла\t\tетос");
									printf("\n_______________________________________________________________________\n\n\n");
									for(i = 0;i <= numOfSigns;i++){
										fscanf(file, "%d %s %s %d",&bufferPlate,bufferBrand,bufferColor,&bufferYear);
										if(bufferYear == numPossible){
											printf("\t%d\t\t%s\t\t%s\t\t%d\n",bufferPlate,bufferBrand,bufferColor,bufferYear);
											state = true;
											}
										}
										printf("\n_______________________________________________________________________\n\n");
										fclose(file);
										printf("\n\t\t 0.   епистяоцг сто аявийо лемоу");
										printf("\n\t\t 1.   меа амафгтгсг");
										printf("\n\n_______________________________________________________________________\n\n");
										printf("\n\n\t\t\tйамте лиа епикоцг : ");	
										fgets(preCheck,100,stdin);
										sscanf(preCheck, "%d", &choice);
										if(choice ==0){ main();
										}else if(choice == 1){search(numOfSigns);
										}else{
											system("cls");printf("\n\n\t\t\tкахос INPUT !\n\n "); system("pause");
										}
									}while(true);									
								}else{
									system("cls");
									printf("\n\t\t\tкахос INPUT !\n\n\t");
									system("pause");
									system("cls");
								}
						}while(state != true);	
					}
				break;
			default:
				system("cls");printf("\n\n\t\t\tкахос INUPUT !\n\n\t");system("pause");
				break;
			}
		}while(true);
}

void replace(int numOfSigns){ 						// ITS A COMBINE FOR DELETE AND ADD NEW METHODS , LITTLE CHANGES !! BUT IT WORKS !!
	int maxPlate = 999,minPlate = 10000;
	char bufferBrand[25] = {0},bufferColor[25]={0},oldBrand[25]={0},oldColor[25]={0};
	int bufferPlate,bufferYear,oldPlate,oldYear;
	//load of plates
	int platesArray[numOfSigns];
	file = fopen("Signs.txt", "r");
	i=0;
   	while (fgets(line, sizeof(line), file)) {
		sscanf(line, "%d", &platesArray[i]);
		maxPlate = (platesArray[i]>maxPlate)? platesArray[i]:maxPlate;
		minPlate = (platesArray[i]<minPlate)? platesArray[i]:minPlate; 
		i++;
	}	
	fclose(file);
	if(minPlate == 10000 && maxPlate == 999){
		system("cls"); printf("\n_______________________________________________________________________\n");
			printf("\n\t\t\t    диацяажг еццяажгс");
			printf("\n_______________________________________________________________________\n\n\n");
			printf("\t\t\tдем упаявеи типота циа ма диацяаьете !\n\n ");
			system("pause"); system("cls");
	}else{
		do{
			int superPlate;
			bool plateExist = false,complete = false;
			bool plateState = false,brandState = false,yearState=false,colorState=false;
			plate = -1;
			system("cls"); printf("\n_______________________________________________________________________\n");
			printf("\n\t\t\t    амамеысг еццяажгс");
			printf("\n_______________________________________________________________________\n");
			printf("\n\t\t 0.   епистяоцг сто аявийо лемоу");
			printf("\n\t\t 1.   деите тис йатавыяилемес пимайидес");
			printf("\n_______________________________________________________________________\n");			
			printf("\n\n\tеисацете пимайида аутойимгтоу поу хекете ма амамеысете\n\tапо %d еыс %d  : ",minPlate,maxPlate);	
			fgets(preCheck,100,stdin);
			sscanf(preCheck, "%d", &superPlate);
			if(superPlate >= minPlate && superPlate <= maxPlate){
				for (i = 0; i <= numOfSigns; i++){	
					if(superPlate == platesArray[i]){
						plateExist = true;				
					}
   				}
				if(plateExist == true){
   					system("cls");
   					int platesArray[numOfSigns];
					//load of plates
					file = fopen("Signs.txt", "r");
					i=0;
 				  	while (fgets(line, sizeof(line), file)) {
						sscanf(line, "%d", &platesArray[i]);
						if(superPlate == platesArray[i]){
							sscanf(line,"%d %s %s %d",&oldPlate,oldBrand,oldColor,&oldYear);		
					}
						i++;
					}	
					fclose(file);
					//input of plates
					do {
						plate = -1;
						printReplaceLabel(1);
						printf("\n\n\tпакиа пимайида %d",oldPlate);
						printf("\n\tеисацете пимайида ,  апо 1000 еыс 9999  : ");	
						fgets(preCheck,100,stdin);
						sscanf(preCheck, "%d", &plate);
						if(plate >= 1000 && plate <=9999){
							for (i = 0; i <= numOfSigns; i++){
								if(plate == platesArray[i] && plate !=oldPlate){
									system("cls");
									printf("\n\t\t   г пимайида упаявеи гдг ! \n\n\t\t");
									system("pause"); system("cls");	
									state = false;
									break;
								}else{
								state = true;
								}
   							}
						}else if(plate == 0){
							plate = -1;
							main();
						}else if (plate == 1){
							printf("\n\n");
							for (i = 0; i < numOfSigns; i++){
       					 		printf("%d\n",platesArray[i]);
    						}
    						printf("\n\tFound %d plates\n",i);
    						printf("\tWhen you're ready "); system("pause"); system("cls");
							}else{
								system("cls");printf("\n\t\t\tкахос INPUT !\n\n\t");system("pause");system("cls");
							}
							}while(state != true);
								system("cls");
							//input of brand
							do{
								state = false;
								numPossible = -1; //if brandNumPossible don't take input remain -1 
								printReplaceLabel(2);
								printf("\n\tепитувглемг еисацыцг пимайидас %d\t\t\t**пакиа пимайида %d",plate,oldPlate);
								printf("\n\n\tпакиа лаяйа аутойимгтоу %s",oldBrand);
								printf("\n\tеисацете лаяйа аутойимгтоу г лиа епикоцг апо то лемоу : ");
								fgets(brand,50,stdin);	
								strtok(brand, "\n");
								sscanf(brand,"%d %s",&numPossible,&brand);
								char brands[50][i];
								file = fopen("brands.txt", "r");
								for(i = 1; i <= brandLines; i++){
									fscanf(file, "%s", brands[i]);
									}
								fclose(file);
								if(numPossible == 0){
									main();
								}else if(numPossible == 1){
									printf("\n");
								file = fopen("brands.txt", "r");
								while ((c = getc(file)) != EOF) /* read the rest of the file */
   									printf("%c", c);
								printf("\n\t When you're ready ");	system("pause");	system("cls");
								fclose(file);
								}else{
								for(i = 1;i <= brandLines;i++){
									if(strcmp(brand,brands[i]) == 0){
										state = true;
										break;
										}
									}	
								if(state == true){
									break;
								}else{
									system("cls");
								printf("\n\t\t\tкахос INPUT !\n\n\t");
								system("pause");
								system("cls");
								}
							}	
						}while(state != true);	
						// input of color
						do {
							numPossible = -1;
							state = false;
							system("cls");printReplaceLabel(3);
							printf("\n\tепитувглемг еисацыцг пимайидас %d\t\t\t**пакиа пимайида %d",plate,oldPlate);
							printf("\n\tепитувглемг еисацыцг лаяйас %s\t\t\t**пакиа лаяйа %s! ",brand,oldBrand);
							printf("\n\n\tпакио вяыла аутойимгтоу %s",oldColor);
							printf("\n\tеисацете вяыла аутойимгтоу г лиа епикоцг апо то лемоу : ");
							fgets(color,50,stdin);
							strtok(color, "\n");
							sscanf(color,"%d %s",&numPossible,&color);		
							i=0;	
							char colors[50][colorLines];	
							file = fopen("colors.txt", "r");
							for(i = 1; i <= colorLines; i++){
								fscanf(file, "%s", colors[i]);
							}
  						  	fclose(file); 	
							if(numPossible == 0){
								main();
							}else if(numPossible == 1){
								printf("\n");
								file = fopen("colors.txt", "r");
								while ((c = getc(file)) != EOF) /* read the rest of the file */
					   			printf("%c", c);
								printf("\n\t When you're ready ");system("pause");
								fclose(file);
							}else{
								for(i = 1;i <= colorLines;i++){
									if(strcmp(color,colors[i]) == 0){
										state = true;
										break;
									}
								}
								if(state == true){
									break;
								}else{
									system("cls");printf("\n\t\t\tкахос INPUT !\n\n\t");system("pause");system("cls");
								}
							}		
						}while(state != true);
						// input of constructor year
						do{
							year = -1;
							state = false;
							system("cls");	printReplaceLabel(4);
							printf("\n\tепитувглемг еисацыцг пимайидас %d\t\t\t**пакиа пимайида %d",plate,oldPlate);
							printf("\n\tепитувглемг еисацыцг лаяйас %s\t\t\t**пакиа лаяйа %s ",brand,oldBrand);
							printf("\n\tепитувглемг еисацыцг вяылатос %s\t\t\t**пакио вяыла %s",color,oldColor);
							printf("\n\n\tпакиа вяомокоциа аутойимгтоу %d",oldYear);
							printf("\n\tеисацете вяомокоциа танимолгсгс : ");			
							fgets(preCheck,100,stdin);
							sscanf(preCheck, "%d", &year);
							if(year >= minYear && year <= maxYear){
								state = true;
							}else if(year == 0){
								year = -1;
								main();
							}else{
								system("cls");printf("\n\t\t\tкахос INPUT !\n\n\t");system("pause");system("cls");
							}	
						}while(state != true);
						//confirmation and save
						if(strcmp(oldColor,color)!=0||strcmp(oldBrand,brand)!=0||year!=oldYear||plate!=oldPlate){
						do{
							char wholeNewText[2048]={0},carToAdd[256]={0},platePre[10]={0},yearPre[10]={0},carToDel[256]={0},carReady[256]={0};
							int plateCheck;
							file = fopen("Signs.txt", "r");
							while (fgets(line, sizeof(line), file)) {
								sscanf(line, "%d", &plateCheck);									
								if(superPlate == plateCheck){
									strcpy(carToDel,line);
								}
							}
							fclose(file);
							sprintf(platePre, "%d", plate);
							sprintf(yearPre, "%d", year);
							strcat(carToAdd,platePre); strcat(carToAdd,"\t\t");
							strcat(carToAdd,brand); strcat(carToAdd,"\t\t");
							strcat(carToAdd,color); strcat(carToAdd,"\t\t");
							strcat(carToAdd,yearPre);
							numPossible = -1;
							system("cls");
							printReplaceLabel(0);
							printf("\n\n\t\t\t пяоеписйопгсг еццяажгс \n");
							printf("\n_______________________________________________________________________\n");
							printf("\n\tпимайида\tлаяйа\t\tвяыла\t\tетос");	
							printf("\n_______________________________________________________________________\n");
							printf("\n+\t%d\t\t%s\t\t%s\t\t%d",plate,brand,color,year);
							printf("\n-\t%s",carToDel);
							printf("\n\n\t йамте лиа епикоцг : ");
							fgets(preCheck,100,stdin);
							sscanf(preCheck, "%d", &numPossible);
							if(numPossible == 0){
								main();
							}else if(numPossible == 2){
								system("cls");	replace(numOfSigns);
							}else if(numPossible == 1 || numPossible == 3){		
   								char wholeText[2048]={0},delCar[256]={0};
								file = fopen("Signs.txt", "r");	
								while (fgets(line, sizeof(line), file)) {
									sscanf(line, "%d", &plateCheck);									
									if(superPlate != plateCheck){
										strcat(wholeText,line);
									}else{
    									strcat(wholeText,carToAdd);
    									strcat(wholeText,"\n");
									}	
    							}
								fclose(file);
								file = fopen("Signs.txt", "w");
    							fprintf(file,"%s",wholeText);
    							fclose(file);			
								if(numPossible ==1){main();}
									if(numPossible ==3){system("cls");replace(numOfSigns);}
								}else {
									system("cls");printf("\n\t\t\tкахос INPUT !\n\n\t");system("pause");system("cls");
								}	
							}while(true);	
						}else{
							system("cls");printf("\n\n\t\tта аутойимгта еимаи та идиа яе лпайакиаяо !\n\n\t"); system("pause"); system("cls"); replace(numOfSigns);
						}
				 	  }else{
				   			system("cls"); printf("\n_______________________________________________________________________\n");
							printf("\n\t\t\t    диацяажг еццяажгс");
							printf("\n_______________________________________________________________________\n");
				   			printf("\n\t\tг пимайида дем бяехгйе ! \n\n");
				   			system("pause"); system("cls");
				 	  }
				}else if(superPlate == 0){
					superPlate = -1;
					main();
				}else if (superPlate == 1){
					printf("\n\n");
					for (i = 0; i < numOfSigns; i++){
        				printf("%d\n",platesArray[i]);
    				}
    				printf("\n\tFound %d plates\n",i);
    				printf("\tWhen you're ready "); system("pause"); system("cls");
				}else{
					system("cls");printf("\n\t\t\tкахос INPUT !\n\n\t");system("pause");system("cls"); 
			}
		}while(true);
	}
}
