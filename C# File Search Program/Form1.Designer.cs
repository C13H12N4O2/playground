namespace File_Search_Program
{
    partial class Form1
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다.
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마십시오.
        /// </summary>
        private void InitializeComponent()
        {
            this.Search_Directory = new System.Windows.Forms.Label();
            this.Search_Bar = new System.Windows.Forms.TextBox();
            this.Search_Bar_Button = new System.Windows.Forms.Button();
            this.Search_View = new System.Windows.Forms.ListView();
            this.File_Name_Format_Bar = new System.Windows.Forms.TextBox();
            this.Search_Button = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // Search_Directory
            // 
            this.Search_Directory.AutoSize = true;
            this.Search_Directory.Location = new System.Drawing.Point(12, 19);
            this.Search_Directory.Name = "Search_Directory";
            this.Search_Directory.Size = new System.Drawing.Size(93, 12);
            this.Search_Directory.TabIndex = 0;
            this.Search_Directory.Text = "검색할 디렉토리";
            this.Search_Directory.Click += new System.EventHandler(this.Search_Directory_Click);
            // 
            // Search_Bar
            // 
            this.Search_Bar.Location = new System.Drawing.Point(111, 12);
            this.Search_Bar.Name = "Search_Bar";
            this.Search_Bar.Size = new System.Drawing.Size(431, 21);
            this.Search_Bar.TabIndex = 1;
            // 
            // Search_Bar_Button
            // 
            this.Search_Bar_Button.Location = new System.Drawing.Point(548, 10);
            this.Search_Bar_Button.Name = "Search_Bar_Button";
            this.Search_Bar_Button.Size = new System.Drawing.Size(75, 23);
            this.Search_Bar_Button.TabIndex = 2;
            this.Search_Bar_Button.Text = "경로";
            this.Search_Bar_Button.UseVisualStyleBackColor = true;
            this.Search_Bar_Button.Click += new System.EventHandler(this.Search_Bar_Button_Click);
            // 
            // Search_View
            // 
            this.Search_View.Location = new System.Drawing.Point(44, 53);
            this.Search_View.Name = "Search_View";
            this.Search_View.Size = new System.Drawing.Size(569, 259);
            this.Search_View.TabIndex = 3;
            this.Search_View.UseCompatibleStateImageBehavior = false;
            // 
            // File_Name_Format_Bar
            // 
            this.File_Name_Format_Bar.Location = new System.Drawing.Point(44, 327);
            this.File_Name_Format_Bar.Name = "File_Name_Format_Bar";
            this.File_Name_Format_Bar.Size = new System.Drawing.Size(361, 21);
            this.File_Name_Format_Bar.TabIndex = 4;
            // 
            // Search_Button
            // 
            this.Search_Button.Location = new System.Drawing.Point(411, 325);
            this.Search_Button.Name = "Search_Button";
            this.Search_Button.Size = new System.Drawing.Size(202, 23);
            this.Search_Button.TabIndex = 5;
            this.Search_Button.Text = "검색";
            this.Search_Button.UseVisualStyleBackColor = true;
            this.Search_Button.Click += new System.EventHandler(this.Search_Button_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(667, 386);
            this.Controls.Add(this.Search_Button);
            this.Controls.Add(this.File_Name_Format_Bar);
            this.Controls.Add(this.Search_View);
            this.Controls.Add(this.Search_Bar_Button);
            this.Controls.Add(this.Search_Bar);
            this.Controls.Add(this.Search_Directory);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label Search_Directory;
        private System.Windows.Forms.TextBox Search_Bar;
        private System.Windows.Forms.Button Search_Bar_Button;
        private System.Windows.Forms.ListView Search_View;
        private System.Windows.Forms.TextBox File_Name_Format_Bar;
        private System.Windows.Forms.Button Search_Button;
    }
}

