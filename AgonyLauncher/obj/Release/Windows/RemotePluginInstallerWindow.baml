   M S B A M L   `   `   `  ���� H  DAgonyLauncher, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null=#clr-namespace:AgonyLauncher.WindowsAgonyLauncher.Windows  A%clr-namespace:AgonyLauncher.ConverterAgonyLauncher.Converter  7    1AgonyLauncher.Windows.RemotePluginInstallerWindow   R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     @d2http://schemas.microsoft.com/expression/blend/2008     Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5local#clr-namespace:AgonyLauncher.Windows     ;	converter%clr-namespace:AgonyLauncher.Converter     -     � Title$  Remote Plugin Installer��$	��380��$	��720��$��1q�
���   � � WindowStartupLocation$ CenterOwner=� � 
ResizeMode$ NoResize=����	#FF333333 � 	Resources  �� MergedDictionaries �� Source;  5AgonyLauncher.Converter.WindowTitleRandomizeConverter   WindowTitleConverter5   /AgonyLauncher.Converter.InverseBooleanConverter  InverseBooleanConverter7   1AgonyLauncher.Converter.BoolToVisibilityConverter  BoolToVisibilityConverter>   8AgonyLauncher.Converter.InverseBoolToVisibilityConverter $  InverseBoolToVisibilityConverter��  �� $# ../Styles/ExpressionDark.xaml?�%<   &	        &	      &	 
     &	              .���  � RowDefinitions �� $	��11* ��� $
��Auto �$��33���� $
��Auto �$	��231���� $	��30* ��� $
��Auto �.+��� -    ��Name$ ProjectLabel��$��1��$	��0 5q�$
��10 0q�$��Select plugin��$��16(�$��1q�y��� *	IsLoading+ �� 	Converter# [ &   System.Windows.Controls.DataGrid  -   	  Name$	 ProjectsDataGrid��$��2��$
 �� IsSynchronizedWithCurrentItem$

 TrueY�   GridLinesVisibility$ Vertical=�   CanUserAddRows .     HeadersVisibility$ Column=�   CanUserReorderColumns .    CanUserResizeColumns .     CanUserSortColumns .     AutoGenerateColumns .     CanUserResizeRows .  $
��Left=�$��Disabled=�$
��Auto=�$
��10 0q�$
��11.5(� J� RenderTransformOrigin$ 0.5,0.5&�$	��231������ *Items+y��� *	IsLoading+# [    Columns 4  .System.Windows.Controls.DataGridTemplateColumn  ,  &System.Windows.Controls.DataGridColumn   MinWidth$ 70Q�   CellTemplate �� .R��� -   $��Center=�$��Center=�$��Center=�$ 0.5,0.5&� d� 	IsChecked �� *	Install+{��� *	Enabled+z�V� .~���  �� ScaleX$
 0.78Q� �� ScaleY$
 0.78Q��� ��    Header �� $��Install��$��SemiBold"�$
��10 0q�0  *System.Windows.Controls.DataGridTextColumn     Width5	  /System.Windows.Controls.DataGridLengthConverter$ *	 1
  +System.Windows.Controls.DataGridBoundColumn 
  Binding �� *
PluginName+ �� $��Plugin��$��SemiBold"�$
��10 0q�$��Stretch=�  $	 120	  �� *Status+ �� $��Status��$��SemiBold"�$
��10 0q�� -    �Name$ StatusProgressBar��$��2��$��Stretch=�$��14��$��Center=� � IsIndeterminate . $
��10 0q�y��� *	IsLoading+# [ �� -   $ StatusLabel��$��2��$��Downloading data...�����	#FF898888$��1q�$��0 5 5 5q�$��13(�$��
10 83 10 0q�y��� *	IsLoading+# [ ��  �� Orientation$ 
Horizontal=�$��4��$��145,0,132,10q�$��Center=�.+��� -     ��Name$  CancelButton��$��Cancel��$
��Bold"�$
��25 6q�{��� *	IsWorking+# [ �� -   $  InstallButton��$��5 0 0 0q�$��Install��$
��Bold"�$
��25 6q�{��� *	IsWorking+# [ 