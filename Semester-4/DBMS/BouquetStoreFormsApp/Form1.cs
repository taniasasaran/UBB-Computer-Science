using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace BouquetStoreFormsApp
{
    public partial class Form1 : Form
    {
        private SqlConnection connection;
        private SqlDataAdapter dataAdapter;
        private DataSet dataSet;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            this.connection = new SqlConnection(getConnectionString());
            this.dataAdapter = new SqlDataAdapter();
            this.dataSet = new DataSet();
            this.childTable.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            this.floristIdBox.ReadOnly = true;
            this.floristIdBox.Enabled = false;
            parentTableLoad();
        }

        private void parentTableLoad()
        {
            this.parentTable.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            dataAdapter.SelectCommand = new SqlCommand("SELECT * FROM Florist", connection);
            this.dataSet.Clear();
            this.dataAdapter.Fill(dataSet, "Florist");

            this.parentTable.DataSource = dataSet.Tables["Florist"];
        }

        private static string getConnectionString()
        {
            return "Data Source = DESKTOP-L43DEKK; Initial Catalog = BouquetStore; Integrated Security = SSPI;";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                // we create the insert command
                dataAdapter.InsertCommand = new SqlCommand("INSERT INTO Occasion(florist_id, name) VALUES (@f, @n)", connection);

                // we add the parameters of the cmd
                dataAdapter.InsertCommand.Parameters.Add("@f", SqlDbType.Int).Value = Int32.Parse(floristIdBox.Text);
                dataAdapter.InsertCommand.Parameters.Add("@n", SqlDbType.VarChar).Value = nameBox.Text;

                connection.Open();
                dataAdapter.InsertCommand.ExecuteNonQuery();
                MessageBox.Show("Inserted Successfully in the Database!", "", MessageBoxButtons.OK, MessageBoxIcon.Information);
                connection.Close();

                dataSet = new DataSet();
                dataAdapter.Fill(dataSet, "Occasion");
                childTable.DataSource = this.dataSet.Tables["Occasion"];

                this.clearTextBoxes();
            }
            catch (Exception ex)
            {

                MessageBox.Show(ex.Message, "", MessageBoxButtons.OK, MessageBoxIcon.Error);
                connection.Close();
            }
        }

        private void deleteButton_Click(object sender, EventArgs e)
        {
            int index = this.childTable.SelectedRows[0].Index;
            DialogResult dialogResult;
            dialogResult = MessageBox.Show("Are you sure?\n You can't undo this action.", "Please confirm deletion", MessageBoxButtons.YesNo, MessageBoxIcon.Question);

            if (dialogResult.Equals(DialogResult.Yes))
            {
                dataAdapter.DeleteCommand = new SqlCommand("DELETE FROM Occasion WHERE occasion_id=@d");
                dataAdapter.DeleteCommand.Parameters.Add("@d", SqlDbType.Int).Value = dataSet.Tables["Occasion"].Rows[index][1];
                dataAdapter.DeleteCommand.Connection = connection;
                this.connection.Open();
                dataAdapter.DeleteCommand.ExecuteNonQuery();
                MessageBox.Show("Successfully deleted from database", "", MessageBoxButtons.OK, MessageBoxIcon.Information);
                this.connection.Close();

                this.dataSet = new DataSet();
                this.dataAdapter.Fill(dataSet, "Occasion");
                childTable.DataSource = dataSet.Tables["Occasion"];

                this.clearTextBoxes();
            }
        }

        private void updateButton_Click(object sender, EventArgs e)
        {
            try
            {
                // take the index of the selected row
                int index = childTable.SelectedRows[0].Index;

                // create the update cmd and add its parameters
                dataAdapter.UpdateCommand = new SqlCommand("UPDATE Occasion SET florist_id = @f, name = @n WHERE occasion_id = @id", connection);

                dataAdapter.UpdateCommand.Parameters.Add("@f", SqlDbType.Int).Value = Int32.Parse(floristIdBox.Text);
                dataAdapter.UpdateCommand.Parameters.Add("@n", SqlDbType.VarChar).Value = nameBox.Text;

                dataAdapter.UpdateCommand.Parameters.Add("@id", SqlDbType.Int).Value = dataSet.Tables["Occasion"].Rows[index][1];

                // open connection and execute the command
                this.connection.Open();
                dataAdapter.UpdateCommand.ExecuteNonQuery();
                MessageBox.Show("Updated succesfull", "", MessageBoxButtons.OK, MessageBoxIcon.Information);
                this.connection.Close();

                // repopulate child table
                this.dataSet = new DataSet();
                this.dataAdapter.Fill(dataSet, "Occasion");
                childTable.DataSource = dataSet.Tables["Occasion"];
                this.clearTextBoxes();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "", MessageBoxButtons.OK, MessageBoxIcon.Error);
                this.connection.Close();
            }
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void nameLabel_Click(object sender, EventArgs e)
        {

        }

        private void clearTextBoxes()
        {
            nameBox.Clear();
            floristIdBox.Clear();
        }

        private void parentTable_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            clearTextBoxes(); // we clear the text boxes

            // take the current selected row
            DataGridViewRow selectedParent = parentTable.SelectedRows[0];
            if (selectedParent.Cells[0].Value.ToString() != String.Empty)
            {
                // we write in the textbox the id of the product type
                this.floristIdBox.Text = selectedParent.Cells[0].Value.ToString();

                if (this.parentTable.SelectedRows.Count > 0)
                {
                    // we take the id of the library 
                    int floristId = Convert.ToInt32(selectedParent.Cells[0].Value);
                    // create a new sql command with the productTypeId parameter
                    dataAdapter.SelectCommand = new SqlCommand("SELECT * FROM Occasion WHERE florist_id = @id", connection);
                    dataAdapter.SelectCommand.Parameters.AddWithValue("@id", floristId);

                    // create a new data set and repopulate the child table
                    dataSet = new DataSet();
                    this.dataAdapter.Fill(dataSet, "Occasion");
                    this.childTable.DataSource = dataSet.Tables["Occasion"];


                }
            }


        }

        private void childTable_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            int index = childTable.SelectedRows[0].Index;
            if (index <= childTable.SelectedRows.Count) // if the selected row is not emtpy
            {
                this.nameBox.Text = dataSet.Tables["Occasion"].Rows[index][0].ToString();
                this.floristIdBox.Text = dataSet.Tables["Occasion"].Rows[index][2].ToString();
            }

        }

    }
}
