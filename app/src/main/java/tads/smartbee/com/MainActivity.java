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

    private DatabaseReference temperatura;
    private TextView tvTempeture;
    private CardView cardView;

    private ChildEventListener childEventListener;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        temperatura = FirebaseHandlerData.getmFirebaseDatabase().getReference().child("temperature");
        tvTempeture = (TextView) findViewById(R.id.temp_tv);

        FirebaseHandlerData.manipulateNode(childEventListener, temperatura, tvTempeture);

        cardView = (CardView) findViewById(R.id.card_temp);

        cardView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(getApplicationContext(), ChartActivity.class);
                startActivity(intent);
            }
        });
    }
}
