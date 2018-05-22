package com.example.doktor_louis.interface_commandes_supermarche;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    int page=0;
    Integer product=0;
    String text;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // product buttons
        // layout : buttonLayout
        final Button button1 = (Button)findViewById(R.id.button1);
        final Button button2 = (Button)findViewById(R.id.button2);
        final Button button3 = (Button)findViewById(R.id.button3);
        final Button button4 = (Button)findViewById(R.id.button4);

        // arrow buttons
        // layout : arrowLayout
        Button buttonRight = (Button)findViewById(R.id.buttonRight);
        Button buttonLeft = (Button)findViewById(R.id.buttonLeft);

        // product description
        // layout : productLayout
        final TextView productText = (TextView)findViewById(R.id.productTextView);
        final ImageView productImageView = (ImageView)findViewById(R.id.productImageView);


        // button click listeners
        button1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                product = (page*4)+1;
                text = product.toString();
                productText.setText(text);
                productImageView.setImageResource(R.drawable.bunny);
            }
        });
        button2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                product = (page*4)+2;
                text = product.toString();
                productText.setText(text);
            }
        });
        button3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                product = (page*4)+3;
                text = product.toString();
                productText.setText(text);
            }
        });
        button4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                product = (page*4)+4;
                text = product.toString();
                productText.setText(text);
            }
        });

        buttonRight.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (page >= 0) {
                    page++;

                    product = (page*4)+1;
                    text = "Produit " + product.toString();
                    button1.setText(text);
                    product = (page*4)+2;
                    text = "Produit " + product.toString();
                    button2.setText(text);
                    product = (page*4)+3;
                    text = "Produit " + product.toString();
                    button3.setText(text);
                    product = (page*4)+4;
                    text = "Produit " + product.toString();
                    button4.setText(text);
                }
            }
        });
        buttonLeft.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (page >= 1) {
                    page--;

                    product = (page*4)+1;
                    text = "Produit " + product.toString();
                    button1.setText(text);
                    product = (page*4)+2;
                    text = "Produit " + product.toString();
                    button2.setText(text);
                    product = (page*4)+3;
                    text = "Produit " + product.toString();
                    button3.setText(text);
                    product = (page*4)+4;
                    text = "Produit " + product.toString();
                    button4.setText(text);
                }
            }
        });
    }
}
