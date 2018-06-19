package tads.smartbee.com.FirebaseManager;

import android.util.Log;
import android.widget.TextView;

import com.google.firebase.database.ChildEventListener;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;


public class FirebaseHandlerData {

    private static FirebaseDatabase mFirebaseDatabase;

    public static FirebaseDatabase getFirebaseDatabase() {
        return mFirebaseDatabase.getInstance();
    }

    public static void manipulateNode(ChildEventListener childEventListener, DatabaseReference databaseReference,
                                      final TextView textView) {

        childEventListener = new ChildEventListener() {
            @Override
            public void onChildAdded(DataSnapshot dataSnapshot, String s) {
                Double temp = dataSnapshot.getValue(Double.class);
                textView.setText(temp.intValue() + "");
                Log.i("TESTEAGAIN", temp + "");
                Log.i("TESTEAGAIN", textView + "");
            }

            @Override
            public void onChildChanged(DataSnapshot dataSnapshot, String s) {
                Double temp = dataSnapshot.getValue(Double.class);
                textView.setText(temp.intValue() + "");
            }

            @Override
            public void onChildRemoved(DataSnapshot dataSnapshot) {

            }

            @Override
            public void onChildMoved(DataSnapshot dataSnapshot, String s) {

            }

            @Override
            public void onCancelled(DatabaseError databaseError) {

            }
        };
        databaseReference.addChildEventListener(childEventListener);
    }

}
