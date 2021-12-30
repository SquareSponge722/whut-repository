package com.qst.dms.net;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

import com.qst.dms.entity.MatchedLogRec;
import com.qst.dms.entity.MatchedTransport;
import com.qst.dms.service.LogRecService;
import com.qst.dms.service.TransportService;
import com.qst.dms.ui.LoginFrame;
import com.qst.dms.ui.MainFrame_temp;

public class DmsNetServer {
    
    public DmsNetServer() {
        new AcceptLogThread(6666).start();
        new AcceptTransThread(6668).start();
        System.out.println("backend started...");
    }

    private class AcceptLogThread extends Thread {
        private ServerSocket serverSocket;
        private Socket socket;
        private LogRecService logRecService;
        private ObjectInputStream ois;

        public AcceptLogThread(int port) {
            logRecService = new LogRecService();
            try {
                serverSocket = new ServerSocket(port);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        @Override
        public void run() {
            while(this.isAlive()){
                try {
                    socket = serverSocket.accept();
                    if(socket != null) {
                        ois = new ObjectInputStream(socket.getInputStream());
                        @SuppressWarnings("unchecked")
                        ArrayList<MatchedLogRec> matchedLogRecs = (ArrayList<MatchedLogRec>) ois.readObject();
                        logRecService.saveMatchLogToDB(matchedLogRecs);
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
                try {
                    ois.close();
                    socket.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    private class AcceptTransThread extends Thread {
        private ServerSocket serverSocket;
        private Socket socket;
        private TransportService transportService;
        private ObjectInputStream ois;

        public AcceptTransThread(int port) {
            transportService = new TransportService();
            try {
                serverSocket = new ServerSocket(port);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        @Override
        public void run() {
            while(this.isAlive()){
                try {
                    socket = serverSocket.accept();
                    if(socket != null) {
                        ois = new ObjectInputStream(socket.getInputStream());
                        @SuppressWarnings("unchecked")
                        ArrayList<MatchedTransport> matchedTransports = (ArrayList<MatchedTransport>) ois.readObject();
                        transportService.saveMatchTransportToDB(matchedTransports);
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
                try {
                    ois.close();
                    socket.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static void main(String[] args) {
        new Thread(
            new Runnable() {
                @Override
                public void run() {
                    new DmsNetServer();
                }
            }
        ).start();
        new LoginFrame();
    }
}