package com.example.doktor_louis.interface_commandes_supermarche;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import org.w3c.dom.Text;

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
        final TextView productName = (TextView)findViewById(R.id.productName);
        final TextView productDescription = (TextView)findViewById(R.id.productDescription);
        final TextView productQuantity = (TextView)findViewById(R.id.productQuantity);
        final ImageView productImageView = (ImageView)findViewById(R.id.productImageView);



        product.add(new Product(0,1,1,R.drawable.bunny, "Lapin", "Un gentil lapin", "Dans le jardin"));
        product.add(new Product(1,3,5,R.drawable.bunny, "Lapin", "Un petit lapin", "Dans le jardin"));
        product.add(new Product(2,2,42,R.drawable.fox,  "Renard", "Un rapide renard", "Derrière le bureau"));
        product.add(new Product(3,2,42,R.drawable.fox, "Renard", "Un rusé renard", "Derrière le bureau"));
        product.add(new Product(4,3,5,R.drawable.bunny, "Lapin", "Un gros lapin", "Dans le jardin"));
        product.add(new Product(5,2,42,R.drawable.fox, "Renard", "Un vieux renard", "Derrière le bureau"));

        // button click listeners
        button1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if( ((page*4)+0) <= product.size()-1) {
                    productName.setText(product.get((page*4)+0).getName());
                    productDescription.setText(product.get((page*4)+0).getDescription());
                    productQuantity.setText("x" + product.get((page*4)+0).getQuantity());
                    productImageView.setImageResource(product.get((page*4)+0).getImgId());
                }
            }
        });
        button2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if( ((page*4)+1) <= product.size()-1) {
                    productName.setText(product.get((page*4)+1).getName());
                    productDescription.setText(product.get((page*4)+1).getDescription());
                    productQuantity.setText("x" + product.get((page*4)+1).getQuantity());
                    productImageView.setImageResource(product.get((page*4)+1).getImgId());
                }
            }
        });
        button3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if( ((page*4)+2) <= product.size()-1) {
                    productName.setText(product.get((page*4)+2).getName());
                    productDescription.setText(product.get((page*4)+2).getDescription());
                    productQuantity.setText("x" + product.get((page*4)+2).getQuantity());
                    productImageView.setImageResource(product.get((page*4)+2).getImgId());
                }
            }
        });
        button4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if( ((page*4)+3) <= product.size()-1) {
                    productName.setText(product.get((page*4)+3).getName());
                    productDescription.setText(product.get((page*4)+3).getDescription());
                    productQuantity.setText("x" + product.get((page*4)+3).getQuantity());
                    productImageView.setImageResource(product.get((page*4)+3).getImgId());
                }
            }
        });

        buttonRight.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if ( (page >= 0) && (((1+page)*4) <= product.size()) ){
                    page++;

                    if( ((page*4)+0) <= product.size()-1) {
                        button1.setVisibility(View.VISIBLE);
                        button1.setText(product.get((page*4)+0).getName());
                    } else button1.setVisibility(View.INVISIBLE);

                    if( ((page*4)+1) <= product.size()-1) {
                        button2.setVisibility(View.VISIBLE);
                        button2.setText(product.get((page*4)+1).getName());
                    } else button2.setVisibility(View.INVISIBLE);

                    if( ((page*4)+2) <= product.size()-1) {
                        button3.setVisibility(View.VISIBLE);
                        button3.setText(product.get((page*4)+2).getName());
                    } else button3.setVisibility(View.INVISIBLE);

                    if( ((page*4)+3) <= product.size()-1) {
                        button4.setVisibility(View.VISIBLE);
                        button4.setText(product.get((page*4)+3).getName());
                    } else button4.setVisibility(View.INVISIBLE);
                }
            }
        });
        buttonLeft.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (page >= 1) {
                    page--;

                    if( ((page*4)+0) <= product.size()-1) {
                        button1.setVisibility(View.VISIBLE);
                        button1.setText(product.get((page*4)+0).getName());
                    } else button1.setVisibility(View.INVISIBLE);

                    if( ((page*4)+1) <= product.size()-1) {
                        button2.setVisibility(View.VISIBLE);
                        button2.setText(product.get((page*4)+1).getName());
                    } else button2.setVisibility(View.INVISIBLE);

                    if( ((page*4)+2) <= product.size()-1) {
                        button3.setVisibility(View.VISIBLE);
                        button3.setText(product.get((page*4)+2).getName());
                    } else button3.setVisibility(View.INVISIBLE);

                    if( ((page*4)+3) <= product.size()-1) {
                        button4.setVisibility(View.VISIBLE);
                        button4.setText(product.get((page*4)+3).getName());
                    } else button4.setVisibility(View.INVISIBLE);
                }
            }
        });
    }
}
