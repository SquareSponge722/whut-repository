package com.qst.dms.service;

import java.io.File;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.io.OutputStream;

public class AppendObjectOutputStream extends ObjectOutputStream {

    public static File file = null;

    public AppendObjectOutputStream(OutputStream out) throws IOException {
        super(out);
    }
    
    @Override
    public void writeStreamHeader() throws IOException {
        if(file != null){
            if(file.length() == 0){
                super.writeStreamHeader();
            }
        }else{
            super.writeStreamHeader();
        }
    }
}
