package com.example.doktor_louis.interface_commandes_supermarche;

import android.content.Context;
import android.view.View;
import android.widget.Button;

public class DynamicButton extends android.support.v7.widget.AppCompatButton {

    final int buttonNumber;

    public DynamicButton(int buttonNumber, Context context) {
        super(context);
        this.buttonNumber = buttonNumber;
    }
}
