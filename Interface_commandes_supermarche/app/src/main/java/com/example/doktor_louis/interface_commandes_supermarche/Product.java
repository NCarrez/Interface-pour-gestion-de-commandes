package com.example.doktor_louis.interface_commandes_supermarche;

import android.content.res.Resources;

import com.example.doktor_louis.interface_commandes_supermarche.R;

public class Product {
    private int productId;
    private int quantity;
    private int barcode;
    private int imgId;
    private String name;
    private String description;
    private String place;


    Product(int productId, int quantity, int barcode, int imgId, String name, String description, String place) {
        this.productId = productId;
        this.quantity = quantity;
        this.barcode = barcode;
        this.imgId = imgId;
        this.name = name;
        this.description = description;
        this.place = place;
    }


    public void setProductId(int productId) {
        if(productId >= 1) {
            this.productId = productId;
        }
    }
    public int getProductId() {
        return this.productId;
    }


    public void setQuantity(int quantity) {
        if(quantity >= 1) {
            this.quantity = quantity;
        }
    }
    public int getQuantity() {
        return this.quantity;
    }


    public void setBarcode(int barcode) {
        if(barcode >= 1) {
            this.barcode = barcode;
        }
    }
    public int getBarcode() {
        return this.barcode;
    }

    public int getImgId() {
        return this.imgId;
    }

    public String getName() {
        return this.name;
    }

    public String getDescription() {
        return this.description;
    }
}
