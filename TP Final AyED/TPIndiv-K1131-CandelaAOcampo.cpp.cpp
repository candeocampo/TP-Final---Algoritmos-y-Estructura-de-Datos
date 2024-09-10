#include<iostream>
#include<string.h>
#include<stdio.h>
using namespace std;

struct tAlum{ //tAlum rAlum
	int legajo;
	char nomYape[30];
	int antiguedad;
};

struct Nodo{
	tAlum info;
	Nodo* sig;
};

struct tMateria_archiv{
	int codM;
	char nomMate[30];
	int capacidad;
};


struct tMateria{  //tMateria rMateria
	int codM;
	char nomMate[30];
	int capacidad;
	int disp; //Disponibilidad, que se inicializa con el mismo valor que capacidad y se va a ir incrementando por cada INTENTO de inscripción.
	Nodo* pilaInscrip; //Hago una pila para que en cada materia tenga los dato de los inscriptos.
};

struct tInscrip{ //tInscrip rInscrip
	int legajo;
	int codM;
};

//ARMO FUNCIONES PARA LISTA

void EliminarPrimero(Nodo*&lista, tAlum&rInfo){
	Nodo*ptr=lista;
	rInfo=ptr->info;
	lista=lista->sig;
	delete ptr;
};

void InsertarOrdenado(Nodo*&lista, tAlum rInfo){
	
	Nodo*pnue=new Nodo();
	pnue->info=rInfo;
	if((lista==NULL) || (pnue->info.antiguedad < lista->info.antiguedad)){
		pnue->sig=lista;
		lista=pnue;
	}
	else{
		Nodo*ptr=lista;
		Nodo*antP;
		while((ptr!=NULL) && (pnue->info.antiguedad > ptr->info.antiguedad)){
			antP=ptr;
			ptr=ptr->sig;
		}
		antP->sig=pnue;
		pnue->sig=ptr;	
	}
}	

//ARMO FUNCIONES PARA LA PILA.

void Push(Nodo*&Pila,tAlum rInfo){
	Nodo*pnue=new Nodo();
	pnue->info=rInfo;
	pnue->sig=Pila;
	Pila=pnue;
}

void Pop(Nodo*&Pila,tAlum&rInfo){
	Nodo*aux=Pila;
	rInfo=aux->info;
	Pila=aux->sig;
	delete aux;
}

//FUNCIONES DE ARCHIVOS: ALUMNOS,MATERIAS E INSCRIPCIONES.

void generar_archivo_alumnos(){ //Generamos el archivo de alumnos para cargar los datos.
	
	tAlum rAlum;
	FILE *fAlum=fopen("TPIndiv-K1131-CandelaAOcampo-Alumnos.dat","wb");
	
	cout<<"INGRESO DATOS DE ALUMNOS"<<endl;
	cout<<"___________________________"<<endl;
	cout<<"Ingrese legajo del Alumno: ";
	cin>>rAlum.legajo;
	while(rAlum.legajo!=0){
		cout<<"Ingrese Nombre y Apellido: ";
		fflush(stdin);
		cin.getline(rAlum.nomYape,30);
		cout<<"Ingrese antiguedad: ";
		cin>>rAlum.antiguedad;
		fwrite(&rAlum,sizeof(rAlum),1,fAlum);
		cout<<"___________________________"<<endl;
		cout<<"Ingrese legajo del Alumno: ";
		cin>>rAlum.legajo;
	}
	fclose(fAlum);
}

void leer_archivo_alumnos(){ //Leemos el archivo de alumnos.
	
	tAlum rAlum;
	FILE *fAlum=fopen("TPIndiv-K1131-CandelaAOcampo-Alumnos.dat","rb");
	
	if(fAlum==NULL){
		cout<<"ERROR! No existe el archivo de Alumnos."<<endl;
		return;
	}
	
	fread(&rAlum,sizeof(rAlum),1,fAlum);
	cout<<"______________________________________"<<endl;
	while(!feof(fAlum)){
		cout<<"Legajo: "<<rAlum.legajo<<endl;
		cout<<"Nombre y Apellido: "<<rAlum.nomYape<<endl;
		cout<<"Antiguedad: "<<rAlum.antiguedad<<endl;
		fread(&rAlum,sizeof(rAlum),1,fAlum);
	}
	fclose(fAlum);
}

void generar_archivo_materias(){ //Generamos el archivo de materias.
	
	tMateria rMateria;
	FILE *fMat=fopen("TPIndiv-K1131-CandelaAOcampo-Materias.dat","wb");
	
	cout<<"CARGA DE ARCHIVO DE MATERIAS"<<endl;
	cout<<"________________________________________"<<endl;
	cout<<"Ingrese Cod de Materia (0 para cortar): "<<endl;
	cin>>rMateria.codM;
	while(rMateria.codM!=0){
		cout<<"Ingrese Nombre de la Materia: ";
		fflush(stdin);
		cin.getline(rMateria.nomMate,30);
		cout<<"Ingrese capacidad de alumnos: ";
		cin>>rMateria.capacidad;
		fwrite(&rMateria,sizeof(rMateria),1,fMat);
		cout<<"________________________________________"<<endl;
		cout<<"Ingrese Cod de Materia (0 para cortar): "<<endl;
		cin>>rMateria.codM;
	}
	fclose(fMat);	
}

void leer_archivo_materias(){ //Leemos el archivo de materias.
	
	tMateria rMateria;
	FILE *fMat=fopen("TPIndiv-K1131-CandelaAOcampo-Materias.dat","rb");
	
	if(fMat==NULL){
		cout<<"ERROR! No existe el archivo de materias."<<endl;
		return;
	}
	fread(&rMateria,sizeof(rMateria),1,fMat);
	while(!feof(fMat)){
		cout<<"Cod Materia: "<<rMateria.codM<<endl;
		cout<<"Materia: "<<rMateria.nomMate<<endl;
		cout<<"Capacidad: "<<rMateria.capacidad<<endl;
		fread(&rMateria,sizeof(rMateria),1,fMat);
	}
	fclose(fMat);
}

void generar_archivo_inscripciones(){ //Generamos el archivo de inscripciones.
	
	tInscrip rInscrip;
	FILE *fInsp=fopen("TPIndiv-K1131-CandelaAOcampo-Inscripciones.dat","wb");
	
	cout<<" INSCRIPCIONES A MATERIAS "<<endl;
	cout<<"________________________________"<<endl;
	cout<<"Ingrese legajo (0 para cortar): ";
	cin>>rInscrip.legajo;
	while(rInscrip.legajo!=0){
		cout<<"Ingrese Cod de Materia: ";
		cin>>rInscrip.codM;
		fwrite(&rInscrip,sizeof(rInscrip),1,fInsp);
		cout<<"________________________________"<<endl;
		cout<<"Ingrese legajo (0 para cortar): ";
		cin>>rInscrip.legajo;
	}
	fclose(fInsp);
}

void leer_archivo_inscripciones(){ //Leemos el arhivo de inscripciones.
	
	tInscrip rInscrip;
	FILE *fInsp=fopen("TPIndiv-K1131-CandelaAOcampo-Inscripciones.dat","rb");
	
	if(fInsp==NULL){
		cout<<"ERROR! No existe el archivo de inscripciones."<<endl;
		return;
	}
	fread(&rInscrip,sizeof(rInscrip),1,fInsp);
	while(!feof(fInsp)){
		cout<<"Legajo: "<<rInscrip.legajo<<endl;
		cout<<"Cod Materia: "<<rInscrip.codM<<endl;
		fread(&rInscrip,sizeof(rInscrip),1,fInsp);
	}
	fclose(fInsp);
}

void cargar_alumnos_vector(tAlum*rAlum,int & tope1){ //cargamos el archivo al vector de Alumnos.
	
	tope1=0;
	FILE *fAlum=fopen("TPIndiv-K1131-CandelaAOcampo-Alumnos.dat","rb+");
	
	while(fread(&rAlum[tope1],sizeof(*rAlum),1,fAlum)){
	tope1++;
	}
	fclose(fAlum);
}

void cargar_materias_vector(tMateria vMateria[],int & tope){ //cargamos el archivo al vector de Materia.
	
	tMateria rMateria;
	tope=0;
	FILE *fMat=fopen("TPIndiv-K1131-CandelaAOcampo-Materias.dat","rb");
	
	fread(&rMateria,sizeof(rMateria),1,fMat);
	while(!feof(fMat)){
		vMateria[tope].codM=rMateria.codM;
		strcpy(vMateria[tope].nomMate,rMateria.nomMate); //como está variable es un char usamos stcypy para pasarlo.
		vMateria[tope].capacidad=rMateria.capacidad;
		vMateria[tope].disp=rMateria.capacidad; //Inicializamos la disponibilidad con el mismo vector de capcidad.
		vMateria[tope].pilaInscrip=NULL; //Inicializamos la lista en NULL, la usaremos pa'calcular el PROMEDIO.
		fread(&rMateria,sizeof(rMateria),1,fMat);
		tope++;
	}
	fclose(fMat);
}

int buscar_materias(tMateria rMateria[],int tope2,int codM){
	int n2=tope2-1;
	int posM=0;
	while((posM<n2)&&(rMateria[posM].codM!=codM)){ //voy a empezar por el final y después iré al principio.
		posM++;
	}
	if(posM>n2){
		posM=-1;
	}
	return posM;
}

int buscar_alumnos(tAlum vAlum[],int tope,int legajo){
	int n=tope-1;
	int pos=0;
	while((pos<=n)&&(legajo!=vAlum[pos].legajo)){
		pos++;
	}
	if(pos>n){
		pos=-1;
	}
	return pos;
}

float promeAnt(Nodo*&Pila){ //Desarma toda la pila y va acumulando la cantidad de alumnos y su antiguedad pa'calcular el PROMEDIO.
	
	int acumulador=0;
	int cant=0;
	float promedio;
	
	tAlum rAlum;
	
	while(Pila!=NULL){
		Pop(Pila,rAlum);
		acumulador+=rAlum.antiguedad; //acumula la cant de alumnos
		cant++;
	}
	promedio=(acumulador*1.0)/cant;
	return (promedio);	
}

int main(){
	
	tAlum vAlum[1000];
	tMateria vMateria[40];
	int topeAlum,topeMate;
	int pos_alum,pos_mate;
	int codigo,legajo;
	float promedio;
	int sinInscrip=0;
	int sinCupo=0;
	
	int opcion;
	do{
		cout<<"____________MENU DE OPCIONES____________"<<endl;
		cout<<"| 0) Salir del programa.               |"<<endl;
		cout<<"| 1) Generar archivo de Alumnos.       |"<<endl;
		cout<<"| 2) Generar archivo de Materias.      |"<<endl;
		cout<<"| 3) Generar archivo de Inscripciones. |"<<endl;
		cout<<"| 4) Leer archivo de Alumnos.          |"<<endl; 
		cout<<"| 5) Leer archivo de Materias.         |"<<endl;
		cout<<"| 6) Leer archivo de Inscripciones.    |"<<endl;
		cout<<"| 7) Correr el ejercicio.              |"<<endl;
		cout<<"|______________________________________|"<<endl;
		cout<<" "<<endl;
		cout<<"INGRESE UNA OPCION: ";
		
		cin>>opcion;
		switch(opcion){
			case 0:
				cout<<"Gracias por utilizar el programa :) ."<<endl;
				break;
			case 1:
				generar_archivo_alumnos();
				break;
			case 2:
				generar_archivo_materias();
				break;
			case 3:
				generar_archivo_inscripciones();
				break;
			case 4:
				leer_archivo_alumnos();
				break;
			case 5:
				leer_archivo_materias();
				break;
			case 6:
				leer_archivo_inscripciones();
				break;
			case 7:
				tInscrip rInscrip;
				tAlum rAlum;
				Nodo* listaSinCupo=NULL; //lista de aquellos alumnos q'no tienen cupo.
				FILE *fInsp=fopen("TPIndiv-K1131-CandelaAOcampo-Inscripciones.dat","rb");
				
				cargar_alumnos_vector(vAlum,topeAlum);
				cargar_materias_vector(vMateria,topeMate);
				
				fread(&rInscrip,sizeof(rInscrip),1,fInsp);
				while(!feof(fInsp)){
					pos_mate=buscar_materias(vMateria,topeMate,rInscrip.codM);
					pos_alum=buscar_alumnos(vAlum,topeAlum,rInscrip.legajo);
					
					if(vMateria[pos_mate].disp>0){ //se puede inscribir
						Push(vMateria[pos_mate].pilaInscrip,vAlum[pos_alum]); //Agg en la pila de la materia un registro con los datos de alumno.
					}
					else{ //Si NO quedan lugares.
						InsertarOrdenado(listaSinCupo,vAlum[pos_alum]); //insertamos en la lista "SinCupo" un nuevo registro.
					}
					vMateria[pos_mate].disp--; //Voy restando en la Cantidad Disponible
											   //Si se pudo inscribir es pq hay que restar uno en la cantidad disponible.
											   //y si no quedan cupos, la variable cuenta la cantidad de anotdos.
					fread(&rInscrip,sizeof(rInscrip),1,fInsp);
				}
				fclose(fInsp);
				
				//IMPRIMIMOS.
				cout<<"2) PROMEDIO DE ANTIGUEDAD DE ALUMNOS INSCRIPTOS A C/MATERIA."<<endl;
				cout<<"      MATERIA     |  PROMEDIO ANTIGUEDAD    "<<endl;
				for(int i=0;i<topeMate;i++){ //Rercorremos el vector de materias y en c/una analizo la disponibilidad
					if(vMateria[i].disp<0){ //1-Cantidad de pedidos de inscripción q'no se completaron pq se llenaron cupo.
						sinCupo +=(vMateria[i].disp*(-1)); //La cantidad disponible es negativa por eso la multiplico por -1 para q'quede positivo.
					}
					if(vMateria[i].disp==vMateria[i].capacidad){
						sinInscrip++;
						cout<<"     "<<vMateria[i].nomMate<<"      Sin Inscripciones"<<endl;
					}
					else{
						promedio=promeAnt(vMateria[i].pilaInscrip); //Por c/materia, calculamos el promedio por antiguedad de los alumnos.
						cout<<"        "<<vMateria[i].nomMate<<"          "<<promedio<<endl;
					}
				}
				
				cout<<endl<<"En Total hubo: "<<sinCupo<<" alumnos que no se pudieron inscribir a finales."<<endl;
				cout<<endl<<"1) En Total hubo: "<<sinInscrip<<" materias sin inscripciones."<<endl;
				//listado ordenado por antiguedad de los alumnos q no pudieron inscribirse a una materia por falta de capacidad.
				cout<<endl<<"3) Listado de Alumnos que NO pudieron inscribirse"<<endl;
				cout<<"      NOM Y APE     |     LEGAJO     |    ANTIGUEDAD   "<<endl;
				while(listaSinCupo!=NULL){
					EliminarPrimero(listaSinCupo,rAlum);
					cout<<"       "<<rAlum.nomYape<<"               "<<rAlum.legajo<<"              "<<rAlum.antiguedad<<endl;
				}	
							
				break;
		}
	}
	while(opcion!=0);
	return 0;
}
