package tads.smartbee.com;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.CardView;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import com.google.firebase.FirebaseApp;
import com.google.firebase.database.ChildEventListener;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

import tads.smartbee.com.FirebaseManager.FirebaseHandlerData;

public class MainActivity extends AppCompatActivity {

    private DatabaseReference temperatura1;
    private DatabaseReference temperatura2;
    private DatabaseReference temperatura3;

    private DatabaseReference humidade;
    private DatabaseReference peso;

    private TextView tvTempeture1;
    private TextView tvTempeture2;
    private TextView tvTempeture3;

    private TextView tvHumidade1;
    private TextView tvHumidade2;
    private TextView tvHumidade3;

    private TextView tvPeso1;
    private TextView tvPeso2;
    private TextView tvPeso3;

    private ChildEventListener childEventListTemp1;
    private ChildEventListener childEventListTemp2;
    private ChildEventListener childEventListTemp3;

    private ChildEventListener childEventListHumid1;
    private ChildEventListener childEventListHumid2;
    private ChildEventListener childEventListHumid3;

    private ChildEventListener childEventListPeso;

    private CardView cardView1;
    private CardView cardView2;
    private CardView cardView3;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        listenerTemperature();
        listenerHumidity();

        //Cards clicks
        cardView1 = (CardView) findViewById(R.id.card_col1);
        cardView2 = (CardView) findViewById(R.id.card_col2);
        cardView3 = (CardView) findViewById(R.id.card_col3);

        clickCardCol(cardView1, "colmeia1");
        clickCardCol(cardView2, "colmeia2");
        clickCardCol(cardView3, "colmeia3");
    }


    private void clickCardCol(CardView cardView, final String typeChart) {
        cardView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(getApplicationContext(), ChartActivity.class);
                intent.putExtra("colmeia", typeChart);
                startActivity(intent);
            }
        });
    }


    /**
     * Manipular temperatura obtida via sensor
     */
    private void listenerTemperature() {
        temperatura1 = FirebaseHandlerData.getFirebaseDatabase().getReference("colmeia1").child("temperature");
        tvTempeture1 = (TextView) findViewById(R.id.temp1_tv);
        FirebaseHandlerData.manipulateNode(childEventListTemp1, temperatura1, tvTempeture1);

        temperatura2 = FirebaseHandlerData.getFirebaseDatabase().getReference("colmeia2").child("temperature");
        tvTempeture2 = (TextView) findViewById(R.id.temp2_tv);
        FirebaseHandlerData.manipulateNode(childEventListTemp2, temperatura2, tvTempeture2);

        temperatura3 = FirebaseHandlerData.getFirebaseDatabase().getReference("colmeia3").child("temperature");
        tvTempeture3 = (TextView) findViewById(R.id.temp3_tv);
        FirebaseHandlerData.manipulateNode(childEventListTemp3, temperatura3, tvTempeture3);
    }

    /**
     * Manipular Humidade obtida via sensor
     */
    private void listenerHumidity() {
        humidade = FirebaseHandlerData.getFirebaseDatabase().getReference("colmeia1").child("humidade");

        tvHumidade1 = (TextView) findViewById(R.id.humid1_tv);
        tvHumidade2 = (TextView) findViewById(R.id.humid2_tv);
        tvHumidade3 = (TextView) findViewById(R.id.humid3_tv);

        FirebaseHandlerData.manipulateNode(childEventListHumid1, humidade, tvHumidade1);
        FirebaseHandlerData.manipulateNode(childEventListHumid2, humidade, tvHumidade2);
        FirebaseHandlerData.manipulateNode(childEventListHumid3, humidade, tvHumidade3);
    }

    private void listenerWeight() {
        peso = FirebaseHandlerData.getFirebaseDatabase().getReference("colmeia1").child("peso");

        tvPeso1 = (TextView) findViewById(R.id.peso1_tv);
        tvPeso2 = (TextView) findViewById(R.id.peso2_tv);
        tvPeso3 = (TextView) findViewById(R.id.peso3_tv);

        FirebaseHandlerData.manipulateNode(childEventListPeso, peso, tvPeso1);
        FirebaseHandlerData.manipulateNode(childEventListPeso, peso, tvPeso2);
        FirebaseHandlerData.manipulateNode(childEventListPeso, peso, tvPeso3);
    }
}
