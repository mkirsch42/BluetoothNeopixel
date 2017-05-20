package com.synergydynamics.bluetoothneopixeltest;

import android.Manifest;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Context;
import android.content.pm.PackageManager;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;

import com.flask.colorpicker.ColorPickerView;

import java.io.IOException;
import java.io.OutputStream;
import java.util.UUID;

public class MainActivity extends Activity {

    private static final int REQUEST_BLUETOOTH = 243;

    private OutputStream out;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        BluetoothAdapter bta = BluetoothAdapter.getDefaultAdapter();
        BluetoothDevice btd = bta.getBondedDevices().stream().filter(d->d.getName().startsWith("RNBT")).findFirst().get();
        try {
            BluetoothSocket bts = btd.createRfcommSocketToServiceRecord(UUID.fromString("00001101-0000-1000-8000-00805F9B34FB"));
            bts.connect();
            Log.d("CONNECTED", "CONNECTED");
            out = bts.getOutputStream();
//            ColorPickerDialog cpd = ColorPickerDialog.newBuilder().setColor(0).create();
//            cpd.show(getFragmentManager(), "CPD");
//            cpd.setColorPickerDialogListener(new ColorPickerDialogListener() {
//                @Override
//                public void onColorSelected(int i, int i1) {
//                    Log.d("COLOR_I", ""+i);
//                    Log.d("COLOR_I1", ""+i1);
//                    try {
//                        out.write(new byte[]{'*', (byte) 0b10000011, 0, (byte) Color.red(i), (byte) Color.green(i), (byte) Color.blue(i), 0, 0});
//                    } catch (IOException e) {
//                        e.printStackTrace();
//                    }
//                }
//
//                @Override
//                public void onDialogDismissed(int i) {
//
//                }
//            });

        } catch (IOException e) {
            e.printStackTrace();
        }

        ColorPickerView cpv = (ColorPickerView)findViewById(R.id.color_picker_view);
        cpv.addOnColorChangedListener(c->{try{
            out.write(new byte[]{'*', (byte) 0b10000011, 0, (byte) Color.red(c), (byte) Color.green(c), (byte) Color.blue(c), 0, 0});
        } catch(IOException e) {
            e.printStackTrace();
        }});

    }
}
