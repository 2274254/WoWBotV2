   M S B A M L   `   `   `  ���� H  DAgonyLauncher, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null=#clr-namespace:AgonyLauncher.WindowsAgonyLauncher.Windows  +    %AgonyLauncher.Windows.NewPluginWindow   R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     @d2http://schemas.microsoft.com/expression/blend/2008     Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5local#clr-namespace:AgonyLauncher.Windows     -     � WindowStartupLocation$  CenterOwner=� � Title$ 
New Plugin��$	��380��$	��720�� � 
ResizeMode$ NoResize=����	#FF333333 � 	Resources  �� MergedDictionaries �� Source��  �� $# ../Styles/ExpressionDark.xaml?�%    .���  � RowDefinitions �� $��* ��� $
��Auto ��� $
��Auto ��� $
��Auto ��� $
��Auto ��� $��* ��� $
��Auto � � ColumnDefinitions �� $	��100 ��� $��* ��� $	��100 �.+�	� -    	�Name$ LocalPluginRadiobutton��$
��0 10q�$��1��$��1��$��Local plugin��	 d� 	IsChecked$	 FalseY�
 J� RenderTransformOrigin$
 
0.014,0.48&�z�V� .~���  �� ScaleY$
 1.28Q� �� ScaleX$
 1.28Q��� �� T�  T� X$ 1.988Q� T� Y$ -0.098Q�]� $��1��$��2��.+��� -   $��Right=�$	��...��$
��15 0q�$��15(�
������� J� 	AllowDrop . �� -    ��Name$ LocalPluginTextBox��$��28��$��Center=����	#FFF2F2F2���	#FFD6D6D6$��0q�$��14(�
���   �	� -   $ RemotePluginRadiobutton��$
��0 10q�$��1��$��3��$
	 TrueY�$��Remote plugin��$
 
0.014,0.48&�z�V� .~��� $
 1.28Q�$
 1.28Q��� -   $ RemotePluginTextbox��$��28��$��1��$��4��$��Center=����	#FFF2F2F2���	#FFD6D6D6$��0q�$��14(�
���   ��� $��1��$��6�� �� Orientation$ 
Horizontal=�$��Center=�$��0 0 0 10q�.+��� -   $��Cancel��$
��Bold"�$
��25 8q��� -    ��Name$ InstallButton��$��10 0 0 0q�$��Install��$
��Bold"�$
��25 8q�