using AgonyLauncher.Routines;
using System;
using System.Diagnostics;
using System.Linq;
using System.Windows;
using System.Windows.Controls;

namespace AgonyLauncher.Windows
{
    public class DropdownValue
    {
        public string Name;
        public int Id;
        public DropdownValue(int id, string name)
        {
            Id = id;
            Name = name;
        }
        public override string ToString()
        {
            return Name;
        }
    }
    /// <summary>
    /// Interaction logic for ProcessWindow.xaml
    /// </summary>
    ///
    public partial class ProcessWindow : Window
    {
        public ProcessWindow()
        {
            InitializeComponent();
            RefreshProcesses();
        }

        private void ButtonCancel_Click(object sender, RoutedEventArgs e)
        {
            Environment.Exit(0);
        }

        private void ButtonSelect_Click(object sender, RoutedEventArgs e)
        {
            if(ProcessDropdown.SelectedValue != null)
            {
                var selectedItem = (DropdownValue)ProcessDropdown.SelectedValue;
                if(selectedItem != null)
                {
                    if (!InjectionRoutine.IsProcessInjected(Process.GetProcessById(selectedItem.Id)))
                    {
                        MainWindow.PId = selectedItem.Id;
                        Close();
                    }
                }
            }
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if(MainWindow.PId == 0)
            {
                Environment.Exit(0);
            }
        }

        void RefreshProcesses()
        {
            var selectedValue = ProcessDropdown.SelectedValue;
            ProcessDropdown.Items.Clear();
            foreach (var p in InjectionRoutine.GetWoWProcesses().Where(p => !InjectionRoutine.IsProcessInjected(p) && !string.IsNullOrEmpty(p.MainWindowTitle)))
            {
                ProcessDropdown.Items.Add(new DropdownValue(p.Id, "Wow (" + p.Id + ") - " + p.StartTime.ToShortTimeString()));
            }
            ProcessDropdown.SelectedValue = selectedValue;
            if(ProcessDropdown.SelectedValue == null)
            {
                ProcessDropdown.SelectedValue = ProcessDropdown.Items.OfType<DropdownValue>().FirstOrDefault();
            }
        }

        private void ButtonRefresh_Click(object sender, RoutedEventArgs e)
        {
            RefreshProcesses();
        }

        private void ProcessDropdown_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (ProcessDropdown.SelectedValue != null)
            {
                var selectedItem = (DropdownValue)ProcessDropdown.SelectedValue;
                if (selectedItem != null)
                {
                    if (!InjectionRoutine.IsProcessInjected(Process.GetProcessById(selectedItem.Id)))
                    {
                        ButtonSelect.IsEnabled = true;
                        return;
                    }
                }
            }
            ButtonSelect.IsEnabled = false;
        }
    }
}
