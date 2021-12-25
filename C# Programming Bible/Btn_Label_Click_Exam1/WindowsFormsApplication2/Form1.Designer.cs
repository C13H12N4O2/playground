namespace WindowsFormsApplication2
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
            System.Windows.Forms.Label Event_ex;
            this.btnClickThis = new System.Windows.Forms.Button();
            this.lblHelloWorld = new System.Windows.Forms.Label();
            this.chk_ex = new System.Windows.Forms.Label();
            this.delegate_example = new System.Windows.Forms.Label();
            Event_ex = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // btnClickThis
            // 
            this.btnClickThis.Location = new System.Drawing.Point(102, 67);
            this.btnClickThis.Name = "btnClickThis";
            this.btnClickThis.Size = new System.Drawing.Size(75, 23);
            this.btnClickThis.TabIndex = 0;
            this.btnClickThis.Text = "button1";
            this.btnClickThis.UseVisualStyleBackColor = true;
            this.btnClickThis.Click += new System.EventHandler(this.btnClickThis_Click);
            // 
            // lblHelloWorld
            // 
            this.lblHelloWorld.AutoSize = true;
            this.lblHelloWorld.Location = new System.Drawing.Point(120, 123);
            this.lblHelloWorld.Name = "lblHelloWorld";
            this.lblHelloWorld.Size = new System.Drawing.Size(38, 12);
            this.lblHelloWorld.TabIndex = 1;
            this.lblHelloWorld.Text = "label1";
            // 
            // chk_ex
            // 
            this.chk_ex.AutoSize = true;
            this.chk_ex.Location = new System.Drawing.Point(120, 167);
            this.chk_ex.Name = "chk_ex";
            this.chk_ex.Size = new System.Drawing.Size(38, 12);
            this.chk_ex.TabIndex = 2;
            this.chk_ex.Text = "label1";
            // 
            // delegate_example
            // 
            this.delegate_example.AutoSize = true;
            this.delegate_example.Location = new System.Drawing.Point(120, 205);
            this.delegate_example.Name = "delegate_example";
            this.delegate_example.Size = new System.Drawing.Size(38, 12);
            this.delegate_example.TabIndex = 3;
            this.delegate_example.Text = "label1";
            // 
            // Event_ex
            // 
            Event_ex.AutoSize = true;
            Event_ex.Location = new System.Drawing.Point(190, 123);
            Event_ex.Name = "Event_ex";
            Event_ex.Size = new System.Drawing.Size(38, 12);
            Event_ex.TabIndex = 4;
            Event_ex.Text = "label1";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 261);
            this.Controls.Add(Event_ex);
            this.Controls.Add(this.delegate_example);
            this.Controls.Add(this.chk_ex);
            this.Controls.Add(this.lblHelloWorld);
            this.Controls.Add(this.btnClickThis);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnClickThis;
        private System.Windows.Forms.Label lblHelloWorld;
        private System.Windows.Forms.Label chk_ex;
        private System.Windows.Forms.Label delegate_example;
    }
}

