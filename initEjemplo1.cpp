#include <stdio.h>
#include <iostream>
#include <mosquitto.h>

using namespace std;

void iniciar_sesion_de_vuelta(struct mosquitto *mosq, void *userdata, int level, const char *str);
void conexion_de_vuelta(struct mosquitto *mosq, void *userdata, int result);

int main(){
	int i;
	char *host = "localhost";//el nombre de host o la dirección IP a la que se va a conectar.
	int port = 1883;//el puerto de red a conectarse. Por lo general, 1883.
	int keepalive = 60;//el número de segundos después de los cuales el intermediario debe enviar un mensaje PING al cliente si no se ha intercambiado ningún otro mensaje en ese momento.
	bool clean_session = true;//se establece en verdadero para indicar al intermediario que limpie todos los mensajes y suscripciones al desconectar, falso para indicarle que se mantenga.
	struct mosquitto *mosq = NULL;//una instancia válida de mosquitto.
	char* userName;
	char* password;
	
	mosquitto_lib_init();//se debe de llmar antes que cualquier funcion de mosquitto
	mosquitto_lib_cleanup();	 
	mosq = mosquitto_new(NULL, clean_session, NULL);//crea una nueva instacncia de un cliente mosquitto
	
	if(!mosq){
		cout<<"Error fuera de memoria"<<endl;
		return 1;
	}
	
	mosquitto_log_callback_set(mosq, iniciar_sesion_de_vuelta);//Establece la devolución de llamada de registro.
	mosquitto_connect_callback_set(mosq, conexion_de_vuelta);//Establece la devolución de llamada de conexión.
	
	if(mosquitto_connect(mosq, host, port, keepalive)){//Conecta a un MQTT Broker
		cout<<"No se pudo conectar con el Broker"<<endl;
		return 1;
	}
	
	
	if(mosquitto_username_pw_set(mosq, userName, password)){//Configura el nombre de usuario y la contraseña de la instancia mosquitto
		cout<<"Error al identificar al usuario "<<endl;
		return 1;
	}
	cout<<"Usuario y contraseña valida"<<endl;
	
	mosquitto_destroy(mosq);//Se llama para liberar memoria asociada con una instancia de cliente mosquitto.
	mosquitto_lib_cleanup();//Se llama para liberar recursos asosiados con la libreria
	return 0;
	
}

void iniciar_sesion_de_vuelta(struct mosquitto *mosq, void *userdata, int level, const char *str){
	//imprime todos los mensajes de registro independientemente del nivel 
	cout<<str<<endl;
}

void conexion_de_vuelta(struct mosquitto *mosq, void *userdata, int result){
	 if(!result){
        mosquitto_subscribe(mosq, NULL, "topic/#", 2);
    }
    else {
        cout<<"Conexion fallida"<<endl;
    }
}
