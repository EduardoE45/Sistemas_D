/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package com.mycompany.socket;

import java.io.*;
import java.net.*;
/**
 *
 * @author LaloE
 */
public class ServidorTexto {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws IOException{
        
        ServerSocket serverSocket = new ServerSocket(5000);
        System.out.println("Servidor esperando en el puerto 5000...");

        // Esperar la conexión del cliente
        Socket socket = serverSocket.accept();
        System.out.println("Cliente conectado.");

        // Flujo de entrada para recibir mensajes del cliente
        BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        
        // Flujo de salida para enviar mensajes al cliente
        PrintWriter out = new PrintWriter(socket.getOutputStream(), true);

        // Leer mensaje del cliente
        String mensajeCliente = in.readLine();
        System.out.println("Cliente dijo: " + mensajeCliente);

        // Responder al cliente
        String respuesta = "Hola, ¿qué tal?";
        out.println(respuesta);

        // Cerrar conexiones
        in.close();
        out.close();
        socket.close();
        serverSocket.close();
    }
    
}
