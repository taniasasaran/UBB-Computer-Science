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
using System.Configuration;

namespace BouquetStoreFormsApp_2
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
            this.parentIdBox.ReadOnly = true;
            this.parentIdBox.Enabled = false;
            if(ConfigurationManager.AppSettings["ChildNrAttributes"] == "2")
            {
                this.priceBox.Hide();
                this.priceLabel.Hide();
            }
            parentTableLoad();
        }

        private void parentTableLoad()
        {
            this.parentTable.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            dataAdapter.SelectCommand = new SqlCommand(ConfigurationManager.AppSettings["SelectParent"], connection);
            this.dataSet.Clear();
            this.dataAdapter.Fill(dataSet, ConfigurationManager.AppSettings["ParentTableName"]);

            this.parentTable.DataSource = dataSet.Tables[ConfigurationManager.AppSettings["ParentTableName"]];
        }

        private static string getConnectionString()
        {
            return ConfigurationManager.ConnectionStrings["connectionString"].ConnectionString;
        }

        private void insert_Click(object sender, EventArgs e)
        {
            try
            {
                // we create the insert command
                dataAdapter.InsertCommand = new SqlCommand(ConfigurationManager.AppSettings["InsertQuery"], connection);

                // we add the parameters of the cmd
                dataAdapter.InsertCommand.Parameters.Add("@f", SqlDbType.Int).Value = Int32.Parse(parentIdBox.Text);
                dataAdapter.InsertCommand.Parameters.Add("@n", SqlDbType.VarChar).Value = nameBox.Text;
                if (ConfigurationManager.AppSettings["ChildNrAttributes"] == "3")
                    dataAdapter.InsertCommand.Parameters.Add("@p", SqlDbType.Int).Value = Int32.Parse(priceBox.Text);

                connection.Open();
                dataAdapter.InsertCommand.ExecuteNonQuery();
                MessageBox.Show("Inserted Successfully in the Database!", "", MessageBoxButtons.OK, MessageBoxIcon.Information);
                connection.Close();

                dataSet = new DataSet();
                dataAdapter.Fill(dataSet, ConfigurationManager.AppSettings["ChildTableName"]);
                childTable.DataSource = this.dataSet.Tables[ConfigurationManager.AppSettings["ChildTableName"]];

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
                int position = Int32.Parse(ConfigurationManager.AppSettings["PKposition"]);
                dataAdapter.DeleteCommand = new SqlCommand(ConfigurationManager.AppSettings["DeleteQuery"]);
                dataAdapter.DeleteCommand.Parameters.Add("@d", SqlDbType.Int).Value = dataSet.Tables[ConfigurationManager.AppSettings["ChildTableName"]].Rows[index][position];
                dataAdapter.DeleteCommand.Connection = connection;
                this.connection.Open();
                dataAdapter.DeleteCommand.ExecuteNonQuery();
                MessageBox.Show("Successfully deleted from database", "", MessageBoxButtons.OK, MessageBoxIcon.Information);
                this.connection.Close();

                this.dataSet = new DataSet();
                this.dataAdapter.Fill(dataSet, ConfigurationManager.AppSettings["ChildTableName"]);
                childTable.DataSource = dataSet.Tables[ConfigurationManager.AppSettings["ChildTableName"]];

                this.clearTextBoxes();
            }
        }

        private void updateButton_Click(object sender, EventArgs e)
        {
            try
            {
                // take the index of the selected row
                int position = Int32.Parse(ConfigurationManager.AppSettings["PKposition"]);
                int index = childTable.SelectedRows[0].Index;
                // create the update cmd and add its parameters
                dataAdapter.UpdateCommand = new SqlCommand(ConfigurationManager.AppSettings["UpdateQuery"], connection);

                dataAdapter.UpdateCommand.Parameters.Add("@f", SqlDbType.Int).Value = Int32.Parse(parentIdBox.Text);
                dataAdapter.UpdateCommand.Parameters.Add("@n", SqlDbType.VarChar).Value = nameBox.Text;
                if (ConfigurationManager.AppSettings["ChildNrAttributes"] == "3")
                    dataAdapter.UpdateCommand.Parameters.Add("@p", SqlDbType.Int).Value = Int32.Parse(priceBox.Text);

                dataAdapter.UpdateCommand.Parameters.Add("@id", SqlDbType.Int).Value = dataSet.Tables[ConfigurationManager.AppSettings["ChildTableName"]].Rows[index][position];

                // open connection and execute the command
                this.connection.Open();
                dataAdapter.UpdateCommand.ExecuteNonQuery();
                MessageBox.Show("Updated succesfully", "", MessageBoxButtons.OK, MessageBoxIcon.Information);
                this.connection.Close();

                // repopulate child table
                this.dataSet = new DataSet();
                this.dataAdapter.Fill(dataSet, ConfigurationManager.AppSettings["ChildTableName"]);
                childTable.DataSource = dataSet.Tables[ConfigurationManager.AppSettings["ChildTableName"]];
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
            priceBox.Clear();
            parentIdBox.Clear();
        }

        private void parentTable_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            clearTextBoxes(); // we clear the text boxes
            int position = Int32.Parse(ConfigurationManager.AppSettings["PKpositionPARENT"]);
            // take the current selected row
            DataGridViewRow selectedParent = parentTable.SelectedRows[0];
            if (selectedParent.Cells[position].Value.ToString() != String.Empty)
            {
                // we write in the textbox the id of the product type
                this.parentIdBox.Text = selectedParent.Cells[position].Value.ToString();
                if (this.parentTable.SelectedRows.Count > 0)
                {
                    // we take the id of the library 
                    int parentId = Convert.ToInt32(selectedParent.Cells[position].Value);
                    // create a new sql command with the productTypeId parameter
                    dataAdapter.SelectCommand = new SqlCommand(ConfigurationManager.AppSettings["SelectQuery"], connection);
                    dataAdapter.SelectCommand.Parameters.AddWithValue("@id", parentId);

                    // create a new data set and repopulate the child table
                    dataSet = new DataSet();
                    this.dataAdapter.Fill(dataSet, ConfigurationManager.AppSettings["ChildTableName"]);
                    this.childTable.DataSource = dataSet.Tables[ConfigurationManager.AppSettings["ChildTableName"]];
                }
            }


        }

        private void childTable_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            int index = childTable.SelectedRows[0].Index;
            if (index < childTable.Rows.Count-1)
            {
                this.nameBox.Text = dataSet.Tables[ConfigurationManager.AppSettings["ChildTableName"]].Rows[index][Int32.Parse(ConfigurationManager.AppSettings["NAMEposition"])].ToString();
                this.parentIdBox.Text = dataSet.Tables[ConfigurationManager.AppSettings["ChildTableName"]].Rows[index][Int32.Parse(ConfigurationManager.AppSettings["FKposition"])].ToString();
                if (ConfigurationManager.AppSettings["ChildNrAttributes"] == "3")
                    this.priceBox.Text = dataSet.Tables[ConfigurationManager.AppSettings["ChildTableName"]].Rows[index][Int32.Parse(ConfigurationManager.AppSettings["PRICEposition"])].ToString();
            }
        }


    }
}
