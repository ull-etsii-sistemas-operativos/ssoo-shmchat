/*
 * chatroom.h - Sala de chat multiusuario basada en memoria compartida
 *
 * Este programa de Jesús Torres <jmtorres@ull.es> está bajo una Licencia
 * Creative Commons Public Domain Dedication 1.0.
 *
 *     http://creativecommons.org/publicdomain/zero/1.0/deed.es
 */

#ifndef CHATROOM_H
#define CHATROOM_H

#include <string>

class ChatRoom
{
public:

    ChatRoom();
    ~ChatRoom();

    // Conectar a la sala de chat indicada
    int connectTo(const std::string& chatRoomId, const std::string& username);

    // Ejecutar el chat
    void run();

private:
    struct SharedMessage;

    // Identificador de la sala y nombre del objeto de memoria compartida
    std::string chatRoomId_;
    // Buffer en memoria compartida para el intercambio de mensajes
    SharedMessage* sharedMessage_;
    // Número de secuencia del último mensaje leido con receive()
    unsigned messageReceiveCounter_;
    // Nombre de usuario con el que participar en el chat
    std::string username_;

    // Indicador de si el objeto es el propietario del objeto de memoria
    // compartida. El propietario es el responsable de su destrucción
    bool isSharedMemoryObjectOwner_;

    // Condición para que se detengan los hilos
    bool stopThreads;

    // Leer mensajes desde la entrada estándar y enviarlos a la sala de chat
    void runSender();
    // Recibir mensajes de la sala de chat y mostrarlos por la salida estándar
    void runReceiver();

    // Enviar um mensaje a la sala de chat
    void send(const std::string& message);
    // Recibir un mensaje de la sala de chat
    void receive(std::string& message, std::string& username);

    // Ejecutar el comando indicado y enviar su salida estándar
    void execAndSend(const std::string& command);
};

#endif // CHATROOM_H
