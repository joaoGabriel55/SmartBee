package tads.smartbee.com;

import android.content.Intent;
import android.content.SharedPreferences;
import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.CardView;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import com.afollestad.materialdialogs.DialogAction;
import com.afollestad.materialdialogs.MaterialDialog;
import com.google.firebase.FirebaseApp;
import com.google.firebase.database.ChildEventListener;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

import tads.smartbee.com.FirebaseManager.FirebaseHandlerData;

public class MainActivity extends AppCompatActivity {

    private DatabaseReference temperatura;
    private DatabaseReference peso;
    private DatabaseReference umidade;

    private TextView tvTempeture;

    private TextView tvUmidade;

    private TextView tvPeso;

    private ChildEventListener childEventListTemperatura;
    private ChildEventListener childEventListUmidade;
    private ChildEventListener childEventListPeso;

    private CardView cardView1;
    private CardView cardView2;
    private CardView cardView3;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        getSupportActionBar().setTitle(R.string.label_action_bar);

        SharedPreferences preferences = getSharedPreferences("user_preferences", MODE_PRIVATE);

        if (!preferences.contains("salvar_estado")) {
            FirebaseDatabase.getInstance().setPersistenceEnabled(true);

            generateModal();

            SharedPreferences.Editor editor = preferences.edit();
            editor.putBoolean("salvar_estado", true);
            editor.commit();
        }

        listenerParams();

        /*//Cards clicks
        cardView1 = (CardView) findViewById(R.id.card_col1);
        cardView2 = (CardView) findViewById(R.id.card_col2);
        cardView3 = (CardView) findViewById(R.id.card_col3);*/

        /*clickCardColmeia(cardView1, "colmeia1");
        clickCardColmeia(cardView2, "colmeia2");
        clickCardColmeia(cardView3, "colmeia3");*/
    }

    private void clickCardColmeia(CardView cardView, final String typeChart) {
        cardView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(getApplicationContext(), ChartActivity.class);
                intent.putExtra("colmeia", typeChart);
                startActivity(intent);
            }
        });
    }


    public void generateModal() {
        MaterialDialog dialog = new MaterialDialog.Builder(this)
                .title(R.string.app_name)
                .content(R.string.descricao)
                .positiveText("Ok")
                .onPositive(new MaterialDialog.SingleButtonCallback() {
                    @Override
                    public void onClick(@NonNull MaterialDialog dialog, @NonNull DialogAction which) {
                    }
                })
                .build();
        dialog.show();
    }


    /**
     * Manipular valores obtidos via sensor
     */
    private void listenerParams() {
        temperatura = FirebaseHandlerData.getFirebaseDatabase().getReference("colmeia1").child("temperature");
        tvTempeture = (TextView) findViewById(R.id.temp_tv);
        FirebaseHandlerData.manipulateNewWay(childEventListTemperatura, temperatura, tvTempeture);
//
//        umidade = FirebaseHandlerData.getFirebaseDatabase().getReference("colmeia1").child("humidity");
//        //tvUmidade = (TextView) findViewById(R.id.humid_tv);
//        FirebaseHandlerData.manipulateNewWay(childEventListUmidade, umidade, tvUmidade,false);

        peso = FirebaseHandlerData.getFirebaseDatabase().getReference("colmeia1").child("weight");
        tvPeso = (TextView) findViewById(R.id.peso_tv);
        FirebaseHandlerData.manipulateNewWay(childEventListPeso, peso, tvPeso);
    }

    @Override
    protected void onStop() {
        super.onStop();


    }
}
