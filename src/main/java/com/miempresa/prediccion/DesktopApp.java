import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.FileReader;

public class DesktopApp extends JFrame {
    private ModelParams model;
    private JTextField txtGRE, txtTOEFL, txtUni, txtSOP, txtLOR, txtCGPA, txtResearch;
    private JLabel lblResult;
    private JLabel lblImage;

    public DesktopApp() {
        loadModel();
        initComponents();
    }

    private void loadModel() {
        try {
            Gson gson = new Gson();
            FileReader reader = new FileReader("model.json");
            // Usamos la referencia completa para evitar conflictos
            java.lang.reflect.Type modelType = new TypeToken<ModelParams>(){}.getType();
            model = gson.fromJson(reader, modelType);
            reader.close();
        } catch (Exception e) {
            JOptionPane.showMessageDialog(null, "Error al cargar el modelo JSON: " + e.getMessage());
            System.exit(1);
        }
    }

    private void initComponents() {
        setTitle("Predicción de Admisión");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(500, 600);
        setLayout(new BorderLayout());

        JPanel panelInput = new JPanel(new GridLayout(8, 2, 5, 5));
        panelInput.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        panelInput.add(new JLabel("GRE Score:"));
        txtGRE = new JTextField();
        panelInput.add(txtGRE);

        panelInput.add(new JLabel("TOEFL Score:"));
        txtTOEFL = new JTextField();
        panelInput.add(txtTOEFL);

        panelInput.add(new JLabel("University Rating:"));
        txtUni = new JTextField();
        panelInput.add(txtUni);

        panelInput.add(new JLabel("SOP:"));
        txtSOP = new JTextField();
        panelInput.add(txtSOP);

        panelInput.add(new JLabel("LOR:"));
        txtLOR = new JTextField();
        panelInput.add(txtLOR);

        panelInput.add(new JLabel("CGPA:"));
        txtCGPA = new JTextField();
        panelInput.add(txtCGPA);

        panelInput.add(new JLabel("Research (0 o 1):"));
        txtResearch = new JTextField();
        panelInput.add(txtResearch);

        JButton btnPredict = new JButton("Predecir");
        panelInput.add(btnPredict);
        // Celda vacía para completar la cuadrícula
        panelInput.add(new JLabel(""));

        btnPredict.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                predict();
            }
        });

        lblResult = new JLabel("Resultado: ");
        lblResult.setHorizontalAlignment(SwingConstants.CENTER);
        lblResult.setFont(new Font("Arial", Font.BOLD, 16));

        lblImage = new JLabel();
        lblImage.setHorizontalAlignment(SwingConstants.CENTER);

        add(panelInput, BorderLayout.NORTH);
        add(lblResult, BorderLayout.CENTER);
        add(lblImage, BorderLayout.SOUTH);

        setLocationRelativeTo(null);
        setVisible(true);
    }

    private void predict() {
        try {
            double gre = Double.parseDouble(txtGRE.getText());
            double toefl = Double.parseDouble(txtTOEFL.getText());
            double uni = Double.parseDouble(txtUni.getText());
            double sop = Double.parseDouble(txtSOP.getText());
            double lor = Double.parseDouble(txtLOR.getText());
            double cgpa = Double.parseDouble(txtCGPA.getText());
            double research = Double.parseDouble(txtResearch.getText());

            double[] features = {gre, toefl, uni, sop, lor, cgpa, research};
            double prediction = model.predict(features);
            System.out.println("Debug: Predicción = " + prediction);
            lblResult.setText("Predicción (Chance of Admit): " + String.format("%.4f", prediction));

            // Llamamos al método para mostrar el mensaje flotante con imagen
            if (prediction >= 0.80) {
                showFloatingMessage("¡Kamehameha! ¡Aprobaste!", "images/happy.png");
            } else {
                showFloatingMessage("¡No tienes suficiente poder! Desaprobaste.", "images/sad.png");
            }

        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(this, "Por favor, ingresa valores numéricos válidos.");
        }
    }

    // Método para mostrar un diálogo flotante al estilo Dragon Ball Z
    private void showFloatingMessage(String message, String imagePath) {
        JDialog dialog = new JDialog(this, "Resultado", false);
        dialog.setLayout(new BorderLayout());
        dialog.setSize(300, 300);
        dialog.setLocationRelativeTo(this);

        JLabel lblMessage = new JLabel(message, SwingConstants.CENTER);
        // Se puede usar una fuente estilo "Comic Sans MS" o similar para un toque informal
        lblMessage.setFont(new Font("Comic Sans MS", Font.BOLD, 20));
        lblMessage.setForeground(Color.ORANGE);
        dialog.add(lblMessage, BorderLayout.NORTH);

        ImageIcon icon = new ImageIcon(imagePath);
        // Redimensiona la imagen a 150x150 píxeles
        Image img = icon.getImage().getScaledInstance(150, 150, Image.SCALE_SMOOTH);
        JLabel lblIcon = new JLabel(new ImageIcon(img));
        lblIcon.setHorizontalAlignment(SwingConstants.CENTER);
        dialog.add(lblIcon, BorderLayout.CENTER);

        dialog.setVisible(true);

        // Timer para cerrar el diálogo automáticamente después de 3 segundos
        Timer timer = new Timer(3000, new ActionListener(){
            public void actionPerformed(ActionEvent e){
                dialog.dispose();
            }
        });
        timer.setRepeats(false);
        timer.start();
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new DesktopApp());
    }
}

