package com.example.doktor_louis.interface_commandes_supermarche;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import java.util.ArrayList;


public class MainActivity extends AppCompatActivity {

    int page=0;
    String text;

    ArrayList<Product> product = new ArrayList<Product>();



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

        product.add(new Product(0,1,1,R.drawable.bunny, "Lapin", "Un gentil lapin", "Dans le jardin"));
        product.add(new Product(1,3,5,R.drawable.bunny, "Lapin", "Un gentil lapin", "Dans le jardin"));
        product.add(new Product(2,2,42,R.drawable.fox, "Renard", "Un rusé renard", "Derrière le bureau"));
        product.add(new Product(3,2,42,R.drawable.fox, "Renard", "Un rusé renard", "Derrière le bureau"));
        product.add(new Product(4,3,5,R.drawable.bunny, "Lapin", "Un gentil lapin", "Dans le jardin"));
        product.add(new Product(5,2,42,R.drawable.fox, "Renard", "Un rusé renard", "Derrière le bureau"));

        text = "Taille " + product.size();
        productText.setText(text);

        // button click listeners
        button1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if( ((page*4)+0) <= product.size()-1) {
                    productText.setText(product.get((page*4)+0).getDescription());
                    productImageView.setImageResource(product.get((page*4)+0).getImgId());
                }
            }
        });
        button2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if( ((page*4)+1) <= product.size()-1) {
                    productText.setText(product.get((page*4)+1).getDescription());
                    productImageView.setImageResource(product.get((page*4)+1).getImgId());
                }
            }
        });
        button3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if( ((page*4)+2) <= product.size()-1) {
                    productText.setText(product.get((page*4)+2).getDescription());
                    productImageView.setImageResource(product.get((page*4)+2).getImgId());
                }
            }
        });
        button4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if( ((page*4)+3) <= product.size()-1) {
                    productText.setText(product.get((page*4)+3).getDescription());
                    productImageView.setImageResource(product.get((page*4)+3).getImgId());
                }
            }
        });

        buttonRight.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (page >= 0) {
                    page++;

                    text = "Produit " + ((page*4)+1);
                    button1.setText(text);
                    text = "Produit " + ((page*4)+2);
                    button2.setText(text);
                    text = "Produit " + ((page*4)+3);
                    button3.setText(text);
                    text = "Produit " + ((page*4)+4);
                    button4.setText(text);
                }
            }
        });
        buttonLeft.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (page >= 1) {
                    page--;

                    text = "Produit " + ((page*4)+1);
                    button1.setText(text);
                    text = "Produit " + ((page*4)+2);
                    button2.setText(text);
                    text = "Produit " + ((page*4)+3);
                    button3.setText(text);
                    text = "Produit " + ((page*4)+4);
                    button4.setText(text);
                }
            }
        });
    }
}
