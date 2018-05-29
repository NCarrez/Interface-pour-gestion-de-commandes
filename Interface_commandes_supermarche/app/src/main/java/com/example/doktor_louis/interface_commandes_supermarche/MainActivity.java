package com.example.doktor_louis.interface_commandes_supermarche;

import android.annotation.SuppressLint;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.Set;


public class MainActivity extends AppCompatActivity {

    private int page=0, selectedItem=0;
    private final static int REQUEST_CODE_ENABLE_BLUETOOTH = 0;
    private String text;

    private ArrayList<Product> product = new ArrayList<>();
    private Set<BluetoothDevice> devices;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // product buttons
        // layout : buttonLayout
        final Button button1 = findViewById(R.id.button1);
        final Button button2 = findViewById(R.id.button2);
        final Button button3 = findViewById(R.id.button3);
        final Button button4 = findViewById(R.id.button4);

        // arrow buttons
        // layout : arrowLayout
        Button buttonRight = findViewById(R.id.buttonRight);
        Button buttonLeft = findViewById(R.id.buttonLeft);

        // sold buttons
        // layout : soldLayout
        Button buttonScan = findViewById(R.id.buttonScan);
        Button buttonSoldOut = findViewById(R.id.buttonSoldOut);

        // other buttons
        // layout : otherLayout
        Button buttonOption = findViewById(R.id.buttonOption);
        Button buttonBluetooth = findViewById(R.id.buttonBluetooth);
        Button buttonFinalise = findViewById(R.id.buttonFinalise);

        // product description
        // layout : productLayout
        final TextView productName = findViewById(R.id.productName);
        final TextView productDescription = findViewById(R.id.productDescription);
        final TextView productQuantity = findViewById(R.id.productQuantity);
        final TextView productPlace = findViewById(R.id.productPlace);
        final ImageView productImageView = findViewById(R.id.productImageView);

        // bluetooth adapters
        // TESTING
        final BluetoothAdapter bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();


        product.add(new Product(0,1,1,R.drawable.bunny, "Lapin", "Un gentil lapin", "Dans le jardin"));
        product.add(new Product(1,3,5,R.drawable.bunny, "Lapin", "Un petit lapin", "Dans le jardin"));
        product.add(new Product(2,2,42,R.drawable.fox,  "Renard", "Un rapide renard", "Derrière le bureau"));
        product.add(new Product(3,2,42,R.drawable.fox, "Renard", "Un rusé renard", "Derrière le bureau"));
        product.add(new Product(4,3,5,R.drawable.bunny, "Lapin", "Un gros lapin", "Dans le jardin"));
        product.add(new Product(5,2,42,R.drawable.fox, "Renard", "Un vieux renard", "Derrière le bureau"));


        //Affichage de base
        if( 0 <= product.size()-1) {
            productName.setText(product.get(selectedItem).getName());
            productDescription.setText(product.get(selectedItem).getDescription());
            text = "x" + product.get(selectedItem).getQuantity();
            productQuantity.setText(text);
            text = "Located at:\n" + product.get(selectedItem).getPlace();
            productPlace.setText(text);
            productImageView.setImageResource(product.get(selectedItem).getImgId());
            button1.setVisibility(View.VISIBLE);
            button1.setText(product.get(0).getName());
        } else button1.setVisibility(View.INVISIBLE);

        if( 1 <= product.size()-1) {
            button2.setVisibility(View.VISIBLE);
            button2.setText(product.get(1).getName());
        } else button2.setVisibility(View.INVISIBLE);

        if( 2 <= product.size()-1) {
            button3.setVisibility(View.VISIBLE);
            button3.setText(product.get(2).getName());
        } else button3.setVisibility(View.INVISIBLE);

        if( 3 <= product.size()-1) {
            button4.setVisibility(View.VISIBLE);
            button4.setText(product.get(3).getName());
        } else button4.setVisibility(View.INVISIBLE);


        // product button click listeners
        button1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if( (page*4) <= product.size()-1) {
                    selectedItem = page*4;
                    printProduct(selectedItem,productName,productDescription,productQuantity,productPlace,productImageView);
                }
            }
        });
        button2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if( ((page*4)+1) <= product.size()-1) {
                    selectedItem = (page*4)+1;
                    printProduct(selectedItem,productName,productDescription,productQuantity,productPlace,productImageView);
                }
            }
        });
        button3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if( ((page*4)+2) <= product.size()-1) {
                    selectedItem = (page*4)+2;
                    printProduct(selectedItem,productName,productDescription,productQuantity,productPlace,productImageView);
                }
            }
        });
        button4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if( ((page*4)+3) <= product.size()-1) {
                    selectedItem = (page*4)+3;
                    printProduct(selectedItem,productName,productDescription,productQuantity,productPlace,productImageView);
                }
            }
        });


        //arrow button click listeners
        buttonRight.setOnClickListener(new View.OnClickListener() {
            @SuppressLint("ResourceAsColor")
            @Override
            public void onClick(View v) {
                if ( (page >= 0) && (((1+page)*4) <= product.size()) ){
                    page++;

                    printProductButton(page*4,button1);
                    printProductButton((page*4)+1,button2);
                    printProductButton((page*4)+2,button3);
                    printProductButton((page*4)+3,button4);
                }
            }
        });
        buttonLeft.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (page >= 1) {
                    page--;

                    printProductButton(page*4,button1);
                    printProductButton((page*4)+1,button2);
                    printProductButton((page*4)+2,button3);
                    printProductButton((page*4)+3,button4);
                }
            }
        });


        // sold button click listeners
        buttonScan.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if( (product.get(selectedItem).getQuantity() > 0) && (!product.get(selectedItem).getSoldOut()))
                {
                    product.get(selectedItem).setQuantity(product.get(selectedItem).getQuantity()-1);
                    if (product.get(selectedItem).getQuantity() > 0)
                        text = "x" + product.get(selectedItem).getQuantity();
                    else {
                        printProductButton(page*4,button1);
                        printProductButton((page*4)+1,button2);
                        printProductButton((page*4)+2,button3);
                        printProductButton((page*4)+3,button4);
                        text = "(Done)";
                    }
                    productQuantity.setText(text);
                }
            }
        });
        buttonSoldOut.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if( (product.get(selectedItem).getQuantity() > 0) && (!product.get(selectedItem).getSoldOut()))
                {
                    product.get(selectedItem).setSoldOut(true);
                    text = "(Sold Out)";
                    printProductButton(page*4,button1);
                    printProductButton((page*4)+1,button2);
                    printProductButton((page*4)+2,button3);
                    printProductButton((page*4)+3,button4);
                    productQuantity.setText(text);
                }
            }
        });


        // other buttons click listeners
        buttonOption.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                text = "Options";
                Toast.makeText(getApplicationContext(), text, Toast.LENGTH_SHORT).show();
            }
        });
        buttonBluetooth.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(bluetoothAdapter == null) text = "Pas de bluetooth";
                else {
                    text = "Avec bluetooth";
                    if (!bluetoothAdapter.isEnabled()) {
                        Intent enableBlueTooth = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                        startActivityForResult(enableBlueTooth, REQUEST_CODE_ENABLE_BLUETOOTH);
                    }
                    else {
                        devices = bluetoothAdapter.getBondedDevices();
                        for (BluetoothDevice bluetoothDevice : devices) {
                            text = "Device = " + bluetoothDevice.getName();
                            Toast.makeText(getApplicationContext(), text, Toast.LENGTH_SHORT).show();
                        }
                    }
                }
                Toast.makeText(getApplicationContext(), text, Toast.LENGTH_SHORT).show();

            }
        });
        buttonFinalise.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                boolean soldOut, done;

                done = true;
                soldOut = false;
                for(int i=0; i<product.size(); i++) {
                    if(product.get(i).getSoldOut()) {
                        soldOut = true;
                    }
                    else if(product.get(i).getQuantity()>0) {
                        done = false;
                    }
                }
                if(done) {
                    text = "Order complete";
                    if(soldOut) text = text + " with sold out";
                }
                else {
                    text = "Order incomplete";
                }
                Toast.makeText(getApplicationContext(), text, Toast.LENGTH_SHORT).show();
            }
        });
    }


    private void printProduct(int selectedItem, TextView productName, TextView productDescription, TextView productQuantity, TextView productPlace, ImageView productImageView) {
        String text;

        productName.setText(product.get(selectedItem).getName());
        productDescription.setText(product.get(selectedItem).getDescription());
        if( (product.get(selectedItem).getQuantity() > 0) && (!product.get(selectedItem).getSoldOut()) ) {
            text = "x" + product.get(selectedItem).getQuantity();
            productQuantity.setText(text);
        }
        else if ( (product.get(selectedItem).getQuantity() == 0) && (!product.get(selectedItem).getSoldOut()) ) {
            text = "(Done)";
            productQuantity.setText(text);
        }
        else {
            text = "(Sold Out)";
            productQuantity.setText(text);
        }
        text = "Located at:\n" + product.get(selectedItem).getPlace();
        productPlace.setText(text);
        productImageView.setImageResource(product.get(selectedItem).getImgId());
    }

    private void printProductButton(int selectedItem, Button button) {
        if( selectedItem <= product.size()-1) {
            button.setVisibility(View.VISIBLE);
            button.setText(product.get(selectedItem).getName());
            if( (product.get(selectedItem).getQuantity() == 0) && (!product.get(selectedItem).getSoldOut()) )
                button.setBackgroundTintList(getApplicationContext().getColorStateList(R.color.colorButtonDone));
            if( (product.get(selectedItem).getQuantity() > 0) && (!product.get(selectedItem).getSoldOut()) )
                button.setBackgroundTintList(getApplicationContext().getColorStateList(R.color.colorButtonNormal));
            else if (product.get(selectedItem).getSoldOut())
                button.setBackgroundTintList(getApplicationContext().getColorStateList(R.color.colorButtonSoldOut));
        } else button.setVisibility(View.INVISIBLE);
    }
}
